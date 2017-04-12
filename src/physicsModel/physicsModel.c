/**
 * @file physicsModel.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include <stdlib.h>
#include <string.h>
#include <vectorMaths.h>
#include "../imuCommunication/imuCommunication.h"
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
      /* Adds the last two vectors together and stores it in the second last location */
      add_vector(averages + tail, averages + tail - 1, averages + tail - 1);

      /* Tail shortens */
      tail--;

      /* The "merge-degree" is now one higher */
      degrees[tail]++;

      /* Devide tail by two */
      div_pow_two_vector(1, averages + tail, averages + tail);
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
  model->gyro_ref = streamed_calibration_average(imu_get_angular);
}

void init_ddi_buffer(ddiBuffer* buffer, Vector* init_values) {
    memcpy(buffer->sample_stream, init_values, sizeof(buffer->sample_stream));
}

void ddi(Vector* new_sample, ddiBuffer* buffer) {
  /* Shift stream values one to the left */
  memcpy(buffer->sample_stream, buffer->sample_stream + 1, (SAMPLE_STREAM_SIZE - 1) * sizeof(buffer->sample_stream[0]));

  /* Last stream value is new sample */
  buffer->sample_stream[SAMPLE_STREAM_SIZE - 1] = *new_sample;

  /*
   * Caluclate second derivative and save it in first array slot as we will not need this one in the future
   * We assume
   * @see http://web.stanford.edu/~fringer/teaching/numerical_methods_02/handouts/lecture4.pdf Formula (30)
   */
  /* Add last value to first one */
  add_vector(&buffer->sample_stream[0], &buffer->sample_stream[SAMPLE_STREAM_SIZE - 1], &buffer->sample_stream[0]);

  /* Subtract middle vector from first one twice */
  sub_vector(&buffer->sample_stream[0], &buffer->sample_stream[1], &buffer->sample_stream[0]);
  sub_vector(&buffer->sample_stream[0], &buffer->sample_stream[1], &buffer->sample_stream[0]);

  /* Add second derivative to I1 and save in I1 */
  add_vector(&buffer->sample_stream[0], &buffer->I1, &buffer->I1);

  /* Add I1 to I2 and save in I2 */
  add_vector(&buffer->I1, &buffer->I2, &buffer->I2);

  /* adjusted sample = I2 */
  new_sample = &buffer->I2;
}

void normalize_accel(Vector* accel, Vector* ref) {

}

void normalize_angular(Vector* angular, physicsModel* model) {
  /* Remove the reference so stationary would be 0, 0, 0 */
  sub_vector(angular, &model->gyro_ref, angular);

  /* Remove the drift using DDI */
  ddi(angular, &model->gyro_ddi);
}

void update_model_orientation(physicsModel* model) {
  Vector angular = imu_get_angular();
  normalize_angular(&angular, model);
  add_vector(&angular, &model->orientation, &model->orientation);
}
