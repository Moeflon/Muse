/*
 * physicsModel.h
 */

#ifndef PHYSICS_MODEL_H_
#define PHYSICS_MODEL_H_

#include <imuCommunication.h>
#include <vectorMaths.h>

#define CALIBRATION_ITERATIONS 8192
#define AVERAGING_BUFFER_SIZE 13 /* must be >= lg of iterations but lg is expensive! */

typedef struct physicsModel {
  Vector* orientation;
  Vector* position;
  Vector* accel_ref;
  Vector* gyro_ref;
} physicsModel;

/**
 * @brief creates model
 * @return pointer to model
 */
physicsModel* create_model(void);

/**
 * @brief frees model memory
 * @param pointer to model
 */
void destroy_model(physicsModel*);

/**
 * @brief calculates references for accelerometer measurements
 * @param pointer to model to calibrate
 */
void calibrate_accel(physicsModel*);

/**
 * @brief calculates references for gyroscope measurements
 * @param pointer to model to calibrate
 */
void calibrate_gyro(physicsModel*);

/**
 * @brief normalizes measurement Vector according to reference
 * @param pointer to Vector containing measurement
 * @param pointer to Vector containing reference
 */
void normalize_accel(Vector*, Vector*);

/**
 * @brief normalizes measurement Vector according to reference
 * @param pointer to Vector containing measurement
 * @param pointer to Vector containing reference
 */
void normalize_angular(Vector*, Vector*);

/**
 * @brief adjusts orientation vector according to new measurement
 * @param pointer to model Vector
 */
void update_model_orientation(physicsModel*);

/**
 * @brief adjusts position vector according to new measurement
 * @param pointer to model Vector
 */
void update_model_position(physicsModel*);

#endif
