/**
 * @file physicsModel.h
 * @brief Declares functions to calibrate and interpret accelerometer & gyro data
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef PHYSICS_MODEL_H_
#define PHYSICS_MODEL_H_

#include <vectorMaths.h>
#include "../imuCommunication/imuCommunication.h"

#define CALIBRATION_ITERATIONS 2048
#define AVERAGING_BUFFER_SIZE 11 /* must be >= lg of iterations but lg is expensive! */

#define ANGULAR_DETECTION_TRESHOLD 50
#define DDI_SAMPLE_STREAM_SIZE 3

/* amount to shift orientation right to get degrees * 10 */
#define ORIENTATION_DEG_10_SHR 10

/**
 * @brief Our physicsModel stores the orientation, position and the reference frames we got from the calibration functions
 */
typedef struct physicsModel {
  Vector32 orientation; /**> orientation vector */
  Vector position; /**> position vector */
  Vector accel_ref; /**> accelerometer reference vector */
  Vector gyro_ref; /**> gyroscope reference vector */
  int32_t gravity_norm_squared; /**> vector norm of gravity squared */
} physicsModel;

/**
 * @brief calculates average of #CALIBRATION_ITERATIONS values obtained with the data_provider function with minimal memory usage
 * @param data_provider function pointer to function returning vectors to be averaged
 * @return the average
 */
Vector streamed_calibration_average(Vector (*data_provider)(void));

/**
 * @brief calculates references for accelerometer measurements while device is stationary on a table
 * @param model pointer to model to calibrate
 */
void calibrate_accel(physicsModel* model);

/**
 * @brief calculates references for gyroscope measurements while device is stationary on a table
 * @param model pointer to model to calibrate
 */
void calibrate_gyro(physicsModel* model);

/**
 * @brief normalizes measurement Vector according to reference
 * @param accel pointer to Vector containing measurement
 * @param
 */
void normalize_accel(Vector* accel, physicsModel* model);

/**
 * @brief normalizes measurement Vector according to reference and applies ddi
 * @param angular pointer to Vector containing measurement
 * @param model pointer to model
 */
void normalize_angular(Vector* angular, physicsModel* model);

/**
 * @brief sets up queues for processing and updates model parts
 * @param queues pointer to queues
 * @param model pointer to model
 */
void update_model(imuQueues* queues, physicsModel* model);

/**
 * @brief adjusts orientation vector according to queues
 *        (assumes processing and sampling queues are already swapped)
 * @param queues pointer to queues
 * @param model pointer to model
 */
void update_model_orientation(imuQueues* queues, physicsModel* model);

/**
 * @brief adjusts position vector according to queues
 *        (assumes processing and sampling queues are already swapped)
 * @param queues pointer to queues
 * @param model pointer to physicsModel model
 */
void update_model_position(imuQueues* queues, physicsModel* model);

/**
 * @brief updates pitch & roll with accelerometer data to eliminate drift
 * @param pointer to an orientation
 * @param Vector pointer to Vector acceleration
 */
void complement_orientation(Vector32* orientation, Vector* acceleration);

#endif
