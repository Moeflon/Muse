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
      div_vector(2, averages + tail);
      div_vector(2, averages + tail - 1);

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

void calibrate_accel(physicsModel* model) {

}

void calibrate_gyro(physicsModel* model) {
  _delay_ms(600); /* debounce */
  model->gyro_ref = streamed_calibration_average(imu_get_angular);
}

void init_ddi_buffer32(ddiBuffer32* buffer, Vector32 (*data_provider)()) {
    for(int i = 0; i < DDI_SAMPLE_STREAM_SIZE; i++) {
      buffer->sample_stream[i] = data_provider();
    }
}

void ddi32(Vector32* new_sample, ddiBuffer32* buffer) {
  /* Shift stream values one to the left */
  memcpy(buffer->sample_stream, buffer->sample_stream + 1, (DDI_SAMPLE_STREAM_SIZE - 1) * sizeof(buffer->sample_stream[0]));

  /* Last stream value is new sample */
  buffer->sample_stream[DDI_SAMPLE_STREAM_SIZE - 1] = *new_sample;

  /*
   * Caluclate second derivative and save it in first array slot as we will not need this one in the future
   * @see http://web.stanford.edu/~fringer/teaching/numerical_methods_02/handouts/lecture4.pdf Formula (30)
   */
  /* Add last value to first one */
  add_to_vector(&buffer->sample_stream[0], &buffer->sample_stream[DDI_SAMPLE_STREAM_SIZE - 1]);

  /* Subtract middle vector from first one twice */
  sub_from_vector(&buffer->sample_stream[0], &buffer->sample_stream[1]);
  sub_from_vector(&buffer->sample_stream[0], &buffer->sample_stream[1]);

  /* Add second derivative to I1 */
  add_to_vector(&buffer->I1, &buffer->sample_stream[0]);

  /* Add I1 to I2 */
  add_to_vector(&buffer->I2, &buffer->I1);

  /* adjusted sample = I2 */
  new_sample = &buffer->I2;
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

  for(int i = 0; i < q->size; i++) {
    Vector* val = &q->queue[i];
    normalize_angular(val, model);
    div_vector(2 * IMU_SAMPLE_RATE, val);

    /* Integrate Quaternion rate */
    Quaternion32 measurement = {0, val->x, val->y, val->z};
    mul_quat(&measurement, &model->orientation);
    add_to_quat(&model->orientation, &measurement);

    /* Normalize orientation */
    normalize_quat(&model->orientation);
  }
}

void update_model_position(imuQueues* queues, physicsModel* model) {

}
