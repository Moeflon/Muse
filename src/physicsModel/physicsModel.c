/**
 * @file physicsModel.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <util/delay.h>
#include <vectorMaths.h>

#include "physicsModel.h"
#include "../globals.h"

void calibrate_imu_data(physicsModel* model) {
  volatile imuDataQueues one;
  volatile imuDataQueues two;

  start_sampler(&one, &two);

  for(int i = 0; i < CALIBRATION_ITERATIONS; i++) {
    /* Wait until queues are full */
    imuDataQueues* sampling = g_data_queues_ptrs.sampling;
    do { GPIOR1 = vq_free_space(&sampling->gyro); } while(GPIOR1);

    /* Switch queues so the sampler can go on with new queue */
    swap_data_queues();
    imuDataQueues* processing = g_data_queues_ptrs.processing;

    Vector avg_accel = vq_average(&processing->accel);
    Vector avg_gyro = vq_average(&processing->gyro);
    shr_vector(LG_CALIBRATION_ITERATIONS, &avg_accel);
    shr_vector(LG_CALIBRATION_ITERATIONS, &avg_gyro);

    add_to_vector(&model->accel_ref, &avg_accel);
    add_to_vector(&model->gyro_ref, &avg_gyro);
  }

  /* 4g is INT16_MAX, and the z needs to be 1g at calibrate time */
  model->accel_ref.z -= (INT16_MAX >> 2);

  stop_sampler();
}

void normalize_angular(Vector* angular, physicsModel* model) {
  /* Remove the reference so stationary would be 0, 0, 0 */
  sub_from_vector(angular, &model->gyro_ref);

  /* Really small angular velocities should be 0 */
  if(abs(angular->x) < ANGULAR_DETECTION_TRESHOLD
  && abs(angular->y) < ANGULAR_DETECTION_TRESHOLD
  && abs(angular->z) < ANGULAR_DETECTION_TRESHOLD) {
    clear_vector(angular);
  }
}

void normalize_accel(Vector* accel, physicsModel* model) {
  /* Remove the reference so stationary would be 0, 0, 1g */
  sub_from_vector(accel, &model->accel_ref);
}

void update_model(physicsModel* model) {
  /* Clear processing queues for use as sampling queues and swap
     such that we seperate processing and sampling queues */
  swap_data_queues();

  /* Update model parts */
  update_model_orientation(g_data_queues_ptrs.processing, model);
  update_model_position(g_data_queues_ptrs.processing, model);
}

void update_model_orientation(imuDataQueues* q_data, physicsModel* model) {
  vectorQueue q = q_data->gyro;
  vectorQueue p = q_data->accel;

  for(int i = 0; i < q.size; i++) {
    normalize_angular(&q.queue[i], model);
    normalize_accel(&p.queue[i], model);

    Vector orientation_deg_10;
    shr_vectors(ORIENTATION_DEG_10_SHR, &model->orientation, &orientation_deg_10);
    euler_transform(&q.queue[i], &orientation_deg_10);

    /* Only complement orientation with accel data when linear acceleration is small */
    if(vector_norm_squared(&p.queue[i]) < ACCEL_NSQ_COMPLEMENTARY_TRESHOLD) {
      PORTA = 1; /* check to see whether complement filter is active */
    } else {
      PORTA = 0;
    }

    add_to_vector(&model->orientation, &q.queue[i]);
  }
}

void update_model_position(imuDataQueues* q_data, physicsModel* model) {

}

void complement_orientation(Vector32* orientation, Vector* acceleration){
  int16_t x = acceleration->x;
  int16_t y = acceleration->y;
  int16_t z = acceleration->z;

  /* The argument of sqrt will fit in uint16_t for our applications,
     accounting for the scale of our accel data and the physical conditions we are
     in */
  uint16_t square = ((int32_t)y)*y + ((int32_t)z)*z;

  int32_t pitch = (int32_t)lu_arctan(y, z) << ORIENTATION_DEG_10_SHR;
  int32_t roll = (int32_t)lu_arctan(-x, lu_sqrt(square)) << ORIENTATION_DEG_10_SHR;

  uint8_t shift = 6;
  orientation->x = (((orientation->x << shift) - orientation->x) + pitch) >> shift;
  orientation->y = (((orientation->y << shift) - orientation->y) + roll) >> shift;
}
