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
#include "../physicsSampler/physicsSampler.h"

#define CALIBRATION_ITERATIONS 4
#define LG_CALIBRATION_ITERATIONS 2

#define ANGULAR_DETECTION_TRESHOLD 50
#define ACCEL_NSQ_COMPLEMENTARY_TRESHOLD 8600

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
} physicsModel;

/**
 * @brief calculates references for accelerometer and gyro measurements while device is stationary on a table
 * @param queues pointer to queues
 * @param model pointer to model to calibrate
 */
void calibrate_imu_data(physicsModel* model);

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
 * @param model pointer to model
 */
void update_model(physicsModel* model);

/**
 * @brief adjusts orientation vector according to queues
 *        (assumes processing and sampling queues are already swapped)
 * @param q_data pointer to dataQueues
 * @param model pointer to model
 */
void update_model_orientation(imuDataQueues* q_data, physicsModel* model);

/**
 * @brief adjusts position vector according to queues
 *        (assumes processing and sampling queues are already swapped)
 * @param q_data pointer to dataQueues
 * @param model pointer to physicsModel model
 */
void update_model_position(imuDataQueues* q_data, physicsModel* model);

/**
 * @brief updates pitch & roll with accelerometer data to eliminate drift
 * @param pointer to an orientation
 * @param Vector pointer to Vector acceleration
 */
void complement_orientation(Vector32* orientation, Vector* acceleration);

#endif
