/**
 * @file imuCommunication.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include "imuCommunication.h"

/* Load register and slave address definitions */
#include "imu_registers.h"

void imu_init() {
  WRITE_REG(PWR_MGMT_1, 0);
}

int16_t imu_parse(uint8_t high, uint8_t low) {
  int16_t result; /* Our result is 16-bit and signed */

  /* Lowest 8 bits of 16 bit result are low */
  result |= low;

  /* Shift high bits 8 bits to the left */
  result |= (high << 8);
  return result;
}

int16_t imu_get_x_acceleration() {
  return imu_parse(READ_REG(ACCEL_XOUT_H), READ_REG(ACCEL_XOUT_L));
}

int16_t imu_get_y_acceleration() {
  return imu_parse(READ_REG(ACCEL_YOUT_H), READ_REG(ACCEL_YOUT_L));
}

int16_t imu_get_z_acceleration() {
  return imu_parse(READ_REG(ACCEL_ZOUT_H), READ_REG(ACCEL_ZOUT_L));
}

Vector imu_get_acceleration() {
  Vector accel = { imu_get_x_acceleration(), imu_get_y_acceleration(), imu_get_z_acceleration() };
  return accel;
}

int16_t imu_get_x_angular() {
  return imu_parse(READ_REG(GYRO_XOUT_H), READ_REG(GYRO_XOUT_L));
}

int16_t imu_get_y_angular() {
  return imu_parse(READ_REG(GYRO_YOUT_H), READ_REG(GYRO_YOUT_L));
}

int16_t imu_get_z_angular() {
  return imu_parse(READ_REG(GYRO_ZOUT_H), READ_REG(GYRO_ZOUT_L));
}

Vector imu_get_angular() {
  Vector angular = { imu_get_x_angular(), imu_get_y_angular(), imu_get_z_angular() };
  return angular;
}
