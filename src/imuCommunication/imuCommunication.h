/**
 * @file imuCommunication.h
 * @brief Communicate with IMU and parse the data into Vectors
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef IMU_COMMUNICATION_H_
#define IMU_COMMUNICATION_H_

#define GYRO_MODE 2 /* 1000 degrees/s, see datasheet */
#define GYRO_DEG_S 1000 /**> Degrees per second for maximum value */
#define ACCEL_MODE 1 /* 4g/s, see datasheet */
#define ACCEL_G_S 4 /**> G's for maximum value */
#define IMU_SAMPLE_RATE 312 /* sample rate of IMU in herz */
#define IMU_SAMPLE_RATE_DIVIDER 25 /* Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV), GOR is 8kHz in default filtering */

#include <stdint.h>

#include "../twiProtocol/twiProtocol.h"
#include "../vectorMaths/vectorMaths.h"
#include "../vectorQueue/vectorQueue.h"

/**
 * @brief Sets up IMU with desired settings
 */
void imu_init(void);

/**
 * @brief Sets up IMU registers for samping
 */
void imu_init_sampling(void);

/**
 * @brief Sets up IMU register for sporadic communication
 */
void imu_uninit_sampling(void);

/**
 * @brief Parses high and low bytes to 16-bit int
 * @param high high bits
 * @param low low bits
 * @return 16-bit integer containing acceleration
 */
int16_t imu_parse(uint8_t high, uint8_t low);

/**
 * @brief Gets the x acceleration
 * @return x acceleration
 */
int16_t imu_get_x_acceleration(void);

/**
 * @brief Gets the y acceleration
 * @return y acceleration
 */
int16_t imu_get_y_acceleration(void);

/**
 * @brief Gets the z acceleration
 * @return z acceleration
 */
int16_t imu_get_z_acceleration(void);

/**
 * @brief Gets the acceleration in all directions
 * @return acceleration vector
 */
Vector imu_get_acceleration(void);

/**
 * @brief Gets the x angular velocity
 * @return x angular velocity
 */
int16_t imu_get_x_angular(void);

/**
 * @brief Gets the y angular velocity
 * @return y angular velocity
 */
int16_t imu_get_y_angular(void);

/**
 * @brief Gets the z acceleration
 * @return z acceleration
 */
int16_t imu_get_z_angular(void);

/**
 * @brief Gets the acceleration in all directions
 * @return angular velocity vector
 */
Vector imu_get_angular(void);
#endif
