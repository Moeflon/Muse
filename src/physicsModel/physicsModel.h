/**
 * @file physicsModel.h
 * @brief Declares functions to calibrate and interpret accelerometer & gyro data
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef PHYSICS_MODEL_H_
#define PHYSICS_MODEL_H_

#include "../imuCommunication/imuCommunication.h"
#include "../physicsSampler/physicsSampler.h"
#include "../vectorMaths/vectorMaths.h"
#include "../vectorQueue/vectorQueue.h"

#define CALIBRATION_ITERATIONS 4
#define LG_CALIBRATION_ITERATIONS 2

#define GIMBAL_LOCK_THRESHOLD 800 /* 80 degrees in raw value */

#define ACCEL_DETECTION_TRESHOLD1 150 /* Individual component treshold */
#define ACCEL_DETECTION_TRESHOLD2 300 /* All components at the same time treshold */

#define ANGULAR_DETECTION_TRESHOLD 50 /* All components at the same time treshold */

/* amount to shift raw angular right to get deg/s */
#define ANGULAR_DEG_S_SHIFT 5

/* amount to shift raw orientation right to get degrees * 10 */
#define ORIENTATION_DEG_SHIFT 10

/* amount to shift raw accel right to get accel in g * 8 */
#define ACCEL_G_SHIFT 10

/* amount to shift raw velocity right to get m/s * 64 */
#define VELOCITY_M_S_SHIFT 12

/* amount to shift raw postion right to ~~~cm */
#define POSITION_CM_SHIFT 8

/* Determines amount of accelerometer data to complement gyro data for orientation */
#define COMPLEMENT_SHIFT 4

/* Upper bound for the mean deviation when there is no linear acceleration */
#define ACCEL_NOISE_DEVIATION 200

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
  Vector accel_g; /**> filtered and transformed acceleration vector in g * 8*/
  Vector angular_deg_s; /**> transformed angular velocity (euler angle velocity) in deg/s */
} physicsModel;

/**
 * @brief Calculates references for accelerometer and gyro measurements while device is stationary on a table
 * @param model pointer to model to calibrate
 */
void calibrate_imu_data(physicsModel* model);

/**
 * @brief Normalizes measurement vector according to reference
 * @param accel pointer to vector containing measurement
 * @param
 */
void normalize_accel(Vector* accel, physicsModel* model);

/**
 * @brief Normalizes measurement vector according to reference
 * @param angular pointer to vector containing measurement
 * @param model pointer to model
 */
void normalize_angular(Vector* angular, physicsModel* model);

/**
 * @brief Transforms measurement to inertial frame of reference and filters out gravity
 * @param angular pointer to vector containing measurement
 * @param model pointer to model
 */
void correct_accel(Vector* accel, physicsModel* model);

/**
 * @brief Sets up queues for processing and updates model parts
 * @param model pointer to model
 */
void update_model(physicsModel* model);

/**
 * @brief Only updates the y orientation according to angular when gimbal lock is occuring
 * @param angular pointer to vector containing measurement
 * @param model pointer to model
 */
void update_orientation_y(Vector* angular, physicsModel* model);

/**
 * @brief Complements orientation with pitch & roll from accelerometer data to eliminate drift
 * @param orientation pointer to the orientation vector
 * @param acceleration pointer to acceleration vector
 */
void complement_orientation(Vector32* orientation, Vector* acceleration);

/**
 * @brief Zeroes model accel data but keeps references
 * @param model pointer to model to zero
 */
void zero_model_accel(physicsModel* model);
#endif
