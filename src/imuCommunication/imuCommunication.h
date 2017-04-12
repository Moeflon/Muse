/**
 * @file imuCommunication.h
 * @brief Declares functions that communicate with accelerometer and parse the data into Vectors
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef IMU_COMMUNICATION_H
#define IMU_COMMUNICATION_H

#include <stdint.h>
#include <vectorMaths.h>
#include <twiProtocol.h>

/**
 * @brief sets power mode of IMU to be able to read data
 */
void imu_init(void);

/**
 * @brief parses high and low bytes to 16-bit int
 * @param high high bits
 * @param low low bits
 * @return 16-bit integer containing acceleration
 */
int16_t imu_parse(uint8_t high, uint8_t low);

/**
 * @brief gets the x acceleration
 * @return x acceleration
 */
int16_t imu_get_x_acceleration(void);

/**
 * @brief gets the y acceleration
 * @return y acceleration
 */
int16_t imu_get_y_acceleration(void);

/**
 * @brief gets the z acceleration
 * @return z acceleration
 */
int16_t imu_get_z_acceleration(void);

/**
 * @brief gets the acceleration in all directions
 * @return acceleration vector
 */
Vector imu_get_acceleration(void);

/**
 * @brief gets the x angular velocity
 * @return x angular velocity
 */
int16_t imu_get_x_angular(void);

/**
 * @brief gets the y angular velocity
 * @return y angular velocity
 */
int16_t imu_get_y_angular(void);

/**
 * @brief gets the z acceleration
 * @return z acceleration
 */
int16_t imu_get_z_angular(void);

/**
 * @brief gets the acceleration in all directions
 * @return angular velocity vector
 */
Vector imu_get_angular(void);
#endif
