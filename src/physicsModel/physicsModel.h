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

#define ANGULAR_DETECTION_TRESHOLD1 40 /* Individual component treshold */
#define ANGULAR_DETECTION_TRESHOLD2 50 /* All components at the same time treshold */
#define ACCEL_NSQ_COMPLEMENTARY_TRESHOLD 8500

/* amount to shift raw orientation right to get degrees * 10 */
#define ORIENTATION_DEG_SHIFT 10

/* amount to shift raw velocity right to get m/s * 64 */
#define VELOCITY_M_S_SHIFT 12

/* Upper bound for the mean deviation when there is no linear acceleration */
#define ACCEL_NOISE_DEVIATION 50

/**
 * @brief Our physicsModel stores the orientation, position and the reference frames we got from the calibration functions
 */
typedef struct physicsModel {
  Vector32 orientation_raw; /**> raw orientation vector */
  Vector orientation_deg; /**> orientation vector in degrees * 10 */
  Vector32 position_raw;  /**> position vector */
  Vector32 velocity_raw; /**> raw velocity vector */
  Vector velocity_m_s; /**> velocity vector in m/s * 64 */
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
 * @brief normalizes measurement Vector according to reference
 * @param angular pointer to Vector containing measurement
 * @param model pointer to model
 */
void normalize_angular(Vector* angular, physicsModel* model);

/**
 * @brief transforms measurement to inertial frame of reference
 *        and filters out gravity. Zeros components if small enough
 * @param angular pointer to Vector containing measurement
 * @param model pointer to model
 */
void correct_accel(Vector* accel, physicsModel* model);

/**
 * @brief sets up queues for processing and updates model parts
 * @param model pointer to model
 */
void update_model(physicsModel* model);

/**
 * @brief updates pitch & roll with accelerometer data to eliminate drift
 * @param pointer to an orientation
 * @param Vector pointer to Vector acceleration
 */
void complement_orientation(Vector32* orientation, Vector* acceleration);

#endif
