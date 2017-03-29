/**
 * physicsModel.c
 */
#include <stdlib.h>
#include <string.h>
#include <vectorMaths.h>
#include <imuCommunication.h>
#include "physicsModel.h"

physicsModel* create_model() {
  physicsModel* model = malloc(sizeof(physicsModel));
  model->orientation = calloc(1, sizeof(Vector)); /* zero-initialize */
  model->position = calloc(1, sizeof(Vector)); /* zero-initialize */
  model->accel_ref = malloc(sizeof(Vector));
  model->gyro_ref = malloc(sizeof(Vector));

  /* TODO: Check if allocation worked
     implement error library to show errors */
  return model;
}

void destroy_model(physicsModel* model) {
  /* Free all memory allocated by create_model */
  free(model->orientation);
  free(model->position);
  free(model->accel_ref);
  free(model->gyro_ref);
  free(model);
}

/* Recursive function for calibration functions */
void merge_averages(Vector* averages, uint8_t* degrees, int8_t* tail) {
  if(*tail == 0) return;
  if(degrees[*tail - 1] == degrees[*tail]) {
    /* Adds the last two vectors together and stores it in the second last location */
    add_vector(averages + *tail, averages + *tail - 1, averages + *tail - 1);

    /* Tail shortens */
    (*tail)--;

    /* The "merge-degree" is now one higher */
    degrees[*tail]++;

    /* Devide tail by two */
    div_pow_two_vector(1, averages + *tail, averages + *tail);

    /* Can we merge more? */
    merge_averages(averages, degrees, tail);
  }
  return;
}

void calibrate_accel(physicsModel* model) {

}

void calibrate_gyro(physicsModel* model) {
  Vector averages[AVERAGING_BUFFER_SIZE];
  uint8_t degrees[AVERAGING_BUFFER_SIZE];

  int8_t tail = -1; /* needs to be -1 to have right tail index at call off merge_averages */
  for(int i = 0; i < CALIBRATION_ITERATIONS; i++) {
    tail++;
    averages[tail] = imu_get_angular();
    merge_averages(averages, degrees, &tail);
  }

  /*
   We now have an array of "partial averages"
   for efficiency we don't average these anymore and just
   take the biggest one at the start
  */
  memcpy(model->gyro_ref, averages, sizeof(Vector));
}

void normalize_accel(Vector* accel, Vector* ref) {

}

void normalize_angular(Vector* angular, Vector* ref) {
  sub_vector(angular, ref, angular);
}

void update_model_orientation(physicsModel* model) {
  Vector angular = imu_get_angular();
  normalize_angular(&angular, model->gyro_ref);
  add_vector(&angular, model->orientation, model->orientation);
}
