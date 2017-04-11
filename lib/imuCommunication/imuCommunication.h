/**
 * @file imuCommunication.h
 * @brief Declares functions that communicate with accelerometer and parse the data into Vectors
 */
#ifndef IMU_COMMUNICATION_H
#define IMU_COMMUNICATION_H

#include <twiProtocol.h>
#include <vectorMaths.h>

/* Load register and slave address definitions */
#include "imu_registers.h"

/* Macros so we don't always have to supply our slave address */
#define WRITE_REG(r, d) twi_write_reg(SLV_TWI_ADDR, r, d)
#define READ_REG(r) twi_read_reg(SLV_TWI_ADDR, r)

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
