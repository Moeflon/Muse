/**
 * @file physicsModel.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <vectorMaths.h>

#include "physicsModel.h"

Vector streamed_calibration_average(Vector (*data_provider)(void)) {
  /*
   As a first attempt of filtering our raw data we will try to figure out just how much the sensor is off.
   Whilst the device is stationary on a table we will get a set amount of samples and average those to get a rough estimate of the error.
   To save memory, we will calculate this average on the fly by averaging values added to an array of size lg(CALIBRATION_ITERATIONS)
   and averaging the two last values if they are of the same "degree". Every time an average is calculated, this value's degree increases.

   Example: (numbers in visualized array are the degrees)
   --------
   iteration 1: | 0 | <- first value is added
   iteration 2: | 0 | 0 | <- new value
                | 1 | <- merged
   iteration 3: | 1 | 0 | <- new value
   iteration 4: | 1 | 0 | 0 | <- new value
                | 1 | 1 | <- merged
                | 2 | <- merged again (recursively)
  */
  Vector averages[AVERAGING_BUFFER_SIZE];
  uint8_t degrees[AVERAGING_BUFFER_SIZE];

  int8_t tail = -1; /* needs to be -1 to have 0 tail index at first call off merge_averages */
  for(int i = 0; i < CALIBRATION_ITERATIONS; i++) {
    tail++;
    averages[tail] = data_provider();

    /* Merge same degrees */
    while(tail > 0 && degrees[tail - 1] == degrees[tail]) {
      /* Divide averaging values by two first for overflow protection */
      shr_vector(1, averages + tail);
      shr_vector(1, averages + tail - 1);

      /* Adds the last two vectors together and stores it in the second last location */
      add_to_vector(averages + tail - 1, averages + tail);

      /* Tail shortens */
      tail--;

      /* The "merge-degree" is now one higher */
      degrees[tail]++;
    }
  }

  /*
   We now have an array of "partial averages"
   for efficiency we don't average these anymore and just
   take the one of highest degree (at the start)
  */
  return averages[0];
}

void calibrate_gyro(physicsModel* model) {
  _delay_ms(600); /* debounce */
  model->gyro_ref = streamed_calibration_average(imu_get_angular);
}

void calibrate_accel(physicsModel* model) {
//  model->accel_ref = streamed_calibration_average(imu_get_acceleration);
//  model->gravity_norm_squared = vector_norm_squared(&model->accel_ref);
//  model->accel_ref.z = (model->accel_ref.x + model->accel_ref.y)/2;

// temp
     model->gravity_norm_squared = 70000000;
}

void normalize_angular(Vector* angular, physicsModel* model) {
  /* Remove the reference so stationary would be 0, 0, 0 */
  sub_from_vector(angular, &model->gyro_ref);

    /* Really small angular velocities should be 0 */

    // Misschien i.p.v. &&, voor elke coord afzonderlijk kijken?
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


void update_model(imuQueues* queues, physicsModel* model) {
    /* Clear processing queues for use as sampling queues */
    vq_clear(queues->gyro_processing_ptr);
    vq_clear(queues->accel_processing_ptr);

    /* Sampling queues to processing, new sampling queues */
    vq_swap(&queues->gyro_processing_ptr, &queues->gyro_sample_ptr);
    vq_swap(&queues->accel_processing_ptr, &queues->accel_sample_ptr);

    /* Update model parts */
    update_model_orientation(queues, model);
    update_model_position(queues, model);
}

void update_model_orientation(imuQueues* queues, physicsModel* model) {
  vectorQueue* q = queues->gyro_processing_ptr;
  vectorQueue* p = queues->accel_processing_ptr;

  for(int i = 0; i < q->size; i++) {
    normalize_angular(&q->queue[i], model);
    normalize_accel(&p->queue[i], model);
    Vector orientation_deg_10;
    shr_vectors(ORIENTATION_DEG_10_SHR, &model->orientation, &orientation_deg_10);
    euler_transform(&q->queue[i], &orientation_deg_10);

    // Only complement orientation with accel data when linear acceleration is small
    if(vector_norm_squared(&p->queue[i]) < model->gravity_norm_squared + 500){
      complement_orientation(&model->orientation, &p->queue[i]);
      PORTA = 1; // check to see whether complement filter is active
    } else {
      PORTA = 0;
    }

    add_to_vector(&model->orientation, &q->queue[i]);
  }
}

void update_model_position(imuQueues* queues, physicsModel* model) {

}

void complement_orientation(Vector32* orientation, Vector* acceleration){
  int16_t x = acceleration->x - 200; // temp, until we fix accel calibration
  int16_t y = acceleration->y + 200; // ^
  int16_t z = acceleration->z;

  /* The argument of sqrt will fit in uint16_t for our applications,
     accounting for the scale of our accel data and the physical conditions we are
     in */
  uint16_t square = ((int32_t)y)*y + ((int32_t)z)*z;

  int16_t pitch = lu_arctan(y,z);
  int16_t roll = lu_arctan(-x,lu_sqrt(square));

  uint8_t shift = 5;
  orientation->x = ((orientation->x << shift) - orientation->x + pitch) >> shift;
  orientation->y = ((orientation->y << shift) - orientation->y + roll) >> shift;
}
