/**
 * @file physicsModel.h
 * @brief Declares functions to calibrate and interpret accelerometer data
 */

#ifndef PHYSICS_MODEL_H_
#define PHYSICS_MODEL_H_

#include <imuCommunication.h>
#include <vectorMaths.h>

#define SAMPLE_STREAM_SIZE 3

#define CALIBRATION_ITERATIONS 8192
#define AVERAGING_BUFFER_SIZE 13 /* must be >= lg of iterations but lg is expensive! */

/**
 * @brief The ddiBuffer stores the necessary values to filter out drift by double derivation and integration on the fly
 * @see http://www.mdpi.com/1424-8220/14/12/23230/htm#DigitalFilteringProtocol
 */
typedef struct ddiBuffer {
  Vector sample_stream[SAMPLE_STREAM_SIZE]; /**> Holds three measurements */
  Vector I1; /**> last integration value */
  Vector I2; /**> last double integration value */
} ddiBuffer;

/**
 * @brief Our physicsModel stores the orientation, position and the reference frames we got from the calibration functions
 */
typedef struct physicsModel {
  Vector orientation; /**> orientation vector */
  Vector position; /**> position vector */
  Vector accel_ref; /**> accelerometer reference vector */
  Vector gyro_ref; /**> gyroscope reference vector */
  ddiBuffer gyro_ddi; /**> gyroscope data DDI buffer */
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
 * @brief initializes ddi buffer with given vector of values
 * @param buffer pointer to ddiBuffer struct
 * @param init_values array containing initial values
 */
void init_ddi_buffer(ddiBuffer* buffer, Vector* init_values);

/**
 * @brief Removes the drift from new sample value using buffered values and adjusts buffers for further use
 * @see http://www.mdpi.com/1424-8220/14/12/23230/htm#DigitalFilteringProtocol
 * @param new_sample new sample to undrift
 * @param buffer pointer to ddiBuffer struct
 */
void ddi(Vector* new_sample, ddiBuffer* buffer);

/**
 * @brief normalizes measurement Vector according to reference
 * @param accel pointer to Vector containing measurement
 * @param ref pointer to Vector containing reference
 */
void normalize_accel(Vector* accel, Vector* ref);

/**
 * @brief normalizes measurement Vector according to reference and applies ddi
 * @param angular pointer to Vector containing measurement
 * @param model pointer to model
 */
void normalize_angular(Vector* angular, physicsModel* model);

/**
 * @brief adjusts orientation vector according to new measurement
 * @param model pointer to model
 */
void update_model_orientation(physicsModel* model);

/**
 * @brief adjusts position vector according to new measurement
 * @param model pointer to model Vector
 */
void update_model_position(physicsModel* model);

#endif
