/**
 * @file physicsModel.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <util/delay.h>

#include "../vectorMaths/vectorMaths.h"

#include "physicsModel.h"

void calibrate_imu_data(physicsModel* model) {
  volatile imuDataQueues one = { 0 };
  volatile imuDataQueues two = { 0 };

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
  model->accel_ref.z -= INT16_MAX >> 2;

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

void correct_accel(Vector* accel, physicsModel* model) {
  /* Transform accel measurement to inertial frame of reference */
  euler_transform(accel, &model->orientation_deg);

  /* Remove gravity from z-component */
  accel->z -= (INT16_MAX >> 2);

  /* Bring individual components ACCEL_DETECTION_TRESHOLD1 closer to 0 */
  if(accel->x > ACCEL_DETECTION_TRESHOLD1) accel->x -= ACCEL_DETECTION_TRESHOLD1;
  else if(accel->x < -ACCEL_DETECTION_TRESHOLD1) accel->x += ACCEL_DETECTION_TRESHOLD1;
  else accel->x = 0;

  if(accel->y > ACCEL_DETECTION_TRESHOLD1) accel->y -= ACCEL_DETECTION_TRESHOLD1;
  else if(accel->y < -ACCEL_DETECTION_TRESHOLD1) accel->y += ACCEL_DETECTION_TRESHOLD1;
  else accel->y = 0;

  if(accel->z > ACCEL_DETECTION_TRESHOLD1) accel->z -= ACCEL_DETECTION_TRESHOLD1;
  else if(accel->z < -ACCEL_DETECTION_TRESHOLD1) accel->z += ACCEL_DETECTION_TRESHOLD1;
  else accel->z = 0;

  if(abs(accel->x) < ACCEL_DETECTION_TRESHOLD2
  && abs(accel->y) < ACCEL_DETECTION_TRESHOLD2
  && abs(accel->z) < ACCEL_DETECTION_TRESHOLD2) {
    clear_vector(accel);
  }
}

void update_model(physicsModel* model) {
  /* Clear processing queues for use as sampling queues and swap
     such that we seperate processing and sampling queues */
  swap_data_queues();
  vectorQueue q = g_data_queues_ptrs.processing->gyro;
  vectorQueue p = g_data_queues_ptrs.processing->accel;

  /* Smooth the accel data */
  vq_smooth(&p);

  /* Remove accel peaks using average and deviation */
  Vector accel_avg = vq_average(&q);
  Vector accel_deviation = vq_deviation(&q, &accel_avg);
  vq_remove_peaks(&p, &accel_avg, ACCEL_NOISE_DEVIATION);

  /* Set booleans for no-movement detection */
  int16_t accel_noise_devation_total = p.size * ACCEL_NOISE_DEVIATION;
  uint8_t accel_small_deviation_x = (accel_deviation.x < accel_noise_devation_total) ? 1 : 0;
  uint8_t accel_small_deviation_y = (accel_deviation.y < accel_noise_devation_total) ? 1 : 0;
  uint8_t accel_small_deviation_z = (accel_deviation.z < (accel_noise_devation_total>>1)) ? 1 : 0;
  uint8_t accel_small_deviation = accel_small_deviation_x
                                && accel_small_deviation_y
                                && accel_small_deviation_z;

  for(int i = 0; i < q.size; i++) {
    /* Check for gimbal lock */
    if(abs(model->orientation_deg.y) > GIMBAL_LOCK_THRESHOLD){
      update_orientation_y(model, &q.queue[i]);
      continue;
    }

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
    if(accel_small_deviation) {
      complement_orientation(&model->orientation_raw, &p.queue[i]);
    }

    /* Save angular in model */
    model->angular_deg_s = q.queue[i];
    shr_vector(ANGULAR_DEG_S_SHIFT, &model->angular_deg_s);

    /* Update deg*10 orientation */
    shr_vectors(ORIENTATION_DEG_SHIFT, &model->orientation_raw, &model->orientation_deg);

    /*************************************************************************
     | POSITION PROCESSING                                                   |
     *************************************************************************/
    /* Filter out gravity from accel, and zero if possible */
    correct_accel(&p.queue[i], model);

    /* Save acceleration in model */
    model->accel_g = p.queue[i];
    shr_vector(ACCEL_G_SHIFT, &model->accel_g);

    /* If there's no movement in a particular component, round acceleration to zero to remove drift from velocity */
    if(accel_small_deviation_x) {
      p.queue[i].x = 0;
      model->velocity_raw.x = 0;
    }

    if(accel_small_deviation_y) {
      p.queue[i].y = 0;
      model->velocity_raw.y = 0;
    }

    if(accel_small_deviation_z) {
      p.queue[i].z = 0;
      model->velocity_raw.z = 0;
    }

    /* Integrate acceleration to get velocity */
    add_to_vector(&model->velocity_raw, &p.queue[i]);

    /* Update m/s * 64 velocity */
    shr_vectors(VELOCITY_M_S_SHIFT, &model->velocity_raw, &model->velocity_m_s);

    /* Integrate shifted velocity to both make the scale more manageable and reduce drift */
    add_to_vector(&model->position_raw, &model->velocity_m_s);
  }
}

void update_orientation_y(Vector* angular, physicsModel* model) {
  Vector angular_only_y;
  angular_only_y.y = angular->y;
  add_to_vector(&model->orientation_raw, &angular_only_y);

  /* Update deg*10 orientation */
  shr_vectors(ORIENTATION_DEG_SHIFT, &model->orientation_raw, &model->orientation_deg);
}

void complement_orientation(Vector32* orientation, Vector* acceleration) {
  int16_t x = acceleration->x;
  int16_t y = acceleration->y;
  int16_t z = acceleration->z;

  int32_t pitch = (int32_t)lu_arctan(y, z) << ORIENTATION_DEG_SHIFT;
  int32_t roll = (int32_t)lu_arctan(-x, lu_sqrt32(((uint32_t)y)*y + ((uint32_t)z)*z)) << ORIENTATION_DEG_SHIFT;

  orientation->x = (((orientation->x << COMPLEMENT_SHIFT) - orientation->x) + pitch) >> COMPLEMENT_SHIFT;
  orientation->y = (((orientation->y << COMPLEMENT_SHIFT) - orientation->y) + roll) >> COMPLEMENT_SHIFT;
}

void zero_model_accel(physicsModel* model) {
  Vector32 v = { 0 };
  model->velocity_raw = v;
  model->position_raw = v;
}
