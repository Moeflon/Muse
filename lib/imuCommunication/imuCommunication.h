/**
 * imuCommunication.h
 */
#ifndef IMU_COMMUNICATION_H
#define IMU_COMMUNICATION_H

#include <twiProtocol.h>
#include "imu_registers.h"

#define WRITE_REG(r, d) twi_write_reg(SLV_I2C_ADDR, r, d)
#define READ_REG(r) twi_read_reg(SLV_I2C_ADDR, r)

typedef struct Vector {
  int16_t x;
  int16_t y;
  int16_t z;
} Vector;

/**
 * @brief parses high and low bytes to 16-bit int
 * @param high bits
 * @param low bits
 * @return 16-bit integer containing acceleration
 */
int16_t imu_parse(uint8_t high, uint8_t low);

/**
 * @brief gets the x acceleration
 * @return x acceleration
 */
int16_t imu_get_x_acceleration();

/**
 * @brief gets the y acceleration
 * @return y acceleration
 */
int16_t imu_get_y_acceleration();

/**
 * @brief gets the z acceleration
 * @return z acceleration
 */
int16_t imu_get_z_acceleration();

/**
 * @brief gets the acceleration in all directions
 */
Vector imu_get_acceleration();

/**
 * @brief gets the x angular velocity
 * @return x angular velocity
 */
int16_t imu_get_x_angular();

/**
 * @brief gets the y angular velocity
 * @return y angular velocity
 */
int16_t imu_get_y_angular();

/**
 * @brief gets the z acceleration
 * @return z acceleration
 */
int16_t imu_get_z_angular();

/**
 * @brief gets the acceleration in all directions
 */
Vector imu_get_angular();
#endif
