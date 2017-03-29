/**
 * @file physicsModel.h
 * @brief Declares functions to calibrate and interpret accelerometer data
 */

#ifndef PHYSICS_MODEL_H_
#define PHYSICS_MODEL_H_

#include <imuCommunication.h>
#include <vectorMaths.h>

#define CALIBRATION_ITERATIONS 8192
#define AVERAGING_BUFFER_SIZE 13 /* must be >= lg of iterations but lg is expensive! */

/**
 * @brief Our physicsModel stores the orientation, position and the reference frames we got from the calibration functions
 */
typedef struct physicsModel {
  Vector* orientation; /**> pointer to orientation vector */
  Vector* position; /**> pointer to position vector */
  Vector* accel_ref; /**> pointer to accelerometer reference vector */
  Vector* gyro_ref; /**> pointer to gyroscope reference vector */
} physicsModel;

/**
 * @brief creates model
 * @return pointer to model
 */
physicsModel* create_model(void);

/**
 * @brief frees model memory
 * @param model pointer to model
 */
void destroy_model(physicsModel* model);

/**
 * @brief calculates references for accelerometer measurements
 * @param model pointer to model to calibrate
 */
void calibrate_accel(physicsModel* model);

/**
 * @brief calculates references for gyroscope measurements
 * @param model pointer to model to calibrate
 */
void calibrate_gyro(physicsModel* model);

/**
 * @brief normalizes measurement Vector according to reference
 * @param accel pointer to Vector containing measurement
 * @param ref pointer to Vector containing reference
 */
void normalize_accel(Vector* accel, Vector* ref);

/**
 * @brief normalizes measurement Vector according to reference
 * @param angular pointer to Vector containing measurement
 * @param ref pointer to Vector containing reference
 */
void normalize_angular(Vector* angular, Vector* ref);

/**
 * @brief adjusts orientation vector according to new measurement
 * @param model pointer to model Vector
 */
void update_model_orientation(physicsModel* model);

/**
 * @brief adjusts position vector according to new measurement
 * @param model pointer to model Vector
 */
void update_model_position(physicsModel* model);

#endif
