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
  if(abs(angular->x) < ANGULAR_DETECTION_TRESHOLD1) angular->x = 0;
  if(abs(angular->y) < ANGULAR_DETECTION_TRESHOLD1) angular->y = 0;
  if(abs(angular->z) < ANGULAR_DETECTION_TRESHOLD1) angular->x = 0;

  if(abs(angular->x) < ANGULAR_DETECTION_TRESHOLD2
  && abs(angular->y) < ANGULAR_DETECTION_TRESHOLD2
  && abs(angular->z) < ANGULAR_DETECTION_TRESHOLD2) {
    clear_vector(angular);
  }
}

void normalize_accel(Vector* accel, physicsModel* model) {
  /* Remove the reference so stationary would be 0, 0, 1g */
  sub_from_vector(accel, &model->accel_ref);
}

void correct_accel(Vector* accel, physicsModel* model) {
  /* Transform accel measurement to inertial frame of reference */
  euler_transform(accel, &model->orientation_deg);

  /* Remove gravity from z-component */
  accel->z -= (INT16_MAX >> 2);
}

void update_model(physicsModel* model) {
  /* Clear processing queues for use as sampling queues and swap
     such that we seperate processing and sampling queues */
  swap_data_queues();

  vectorQueue q = g_data_queues_ptrs.processing->gyro;
  vectorQueue p = g_data_queues_ptrs.processing->accel;

  Vector accel_avg = vq_average(&q);
  Vector accel_deviation = vq_deviation(&q, &accel_avg);

  uint16_t accel_noise_devation_total = p.size * ACCEL_NOISE_DEVIATION;
  uint8_t accel_small_deviation_x = (accel_deviation.x < accel_noise_devation_total) ? 1 : 0;
  uint8_t accel_small_deviation_y = (accel_deviation.y < accel_noise_devation_total) ? 1 : 0;
  uint8_t accel_small_deviation_z = (accel_deviation.z < accel_noise_devation_total) ? 1 : 0;

  DDRA = 0xFF;
  PORTA = 0;
  if(accel_small_deviation_x) PORTA |= 8;
  if(accel_small_deviation_y) PORTA |= 4;
  if(accel_small_deviation_z) PORTA |= 2;

  for(int i = 0; i < q.size; i++) {
    /* Crudely normalize measurements for the first time */
    normalize_angular(&q.queue[i], model);
    normalize_accel(&p.queue[i], model);

    /*************************************************************************
     | ORIENTATION PROCESSING                                                |
     *************************************************************************/
    /* Transform measurement according to last orientation in deg*10 */
    euler_transform(&q.queue[i], &model->orientation_deg);

    /* Update raw orientation */
    add_to_vector(&model->orientation_raw, &q.queue[i]);

    /* Only complement orientation with accel data when linear acceleration is small */
    if(vector_norm_squared(&p.queue[i]) < ACCEL_NSQ_COMPLEMENTARY_TRESHOLD) {
      complement_orientation(&model->orientation_raw, &p.queue[i]);
    }

    /* Update deg*10 orientation */
    shr_vectors(ORIENTATION_DEG_SHIFT, &model->orientation_raw, &model->orientation_deg);

    /*************************************************************************
     | POSITION PROCESSING                                                   |
     *************************************************************************/
    /* Filter out gravity from accel, and zero if possible */
    correct_accel(&p.queue[i], model);

    /* Integrate acceleration to get velocity */
    //add_to_vector(&model->velocity_raw, &p.queue[i]);

    /* Update m/s * 64 velocity */
    //shr_vectors(VELOCITY_M_S_SHIFT, &model->velocity_raw, &model->velocity_m_s);
  }

  div_vector(p.size, &accel_deviation);
  model->velocity_m_s = accel_deviation;
}

void complement_orientation(Vector32* orientation, Vector* acceleration){
  int16_t x = acceleration->x;
  int16_t y = acceleration->y;
  int16_t z = acceleration->z;

  int32_t pitch = (int32_t)lu_arctan(y, z) << ORIENTATION_DEG_SHIFT;

  /* The argument of sqrt will fit in uint32_t for our applications,
     accounting for the scale of our accel data and the physical conditions we are
     in */
  int32_t roll = (int32_t)lu_arctan(-x, lu_sqrt32(((uint32_t)y)*y + ((uint32_t)z)*z)) << ORIENTATION_DEG_SHIFT;

  uint8_t shift = 5;
  orientation->x = (((orientation->x << shift) - orientation->x) + pitch) >> shift;
  orientation->y = (((orientation->y << shift) - orientation->y) + roll) >> shift;
}
