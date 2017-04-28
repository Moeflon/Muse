/**
 * @file imuCommunication.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include "imuCommunication.h"

/* Load register and slave address definitions */
#include "registers.h"

void imu_init() {
  PRR0 &= ~_BV(PRTWI); /* TWI enabled */

  WRITE_REG(PWR_MGMT_1, 0); /* Set correct power mode */

  /* Set gyro precision mode */
  uint8_t gyro_config = READ_REG(GYRO_CONFIG);
  gyro_config &= ~(0b11 << FS_SEL); /* sets two FS_SEL places to 0 */
  WRITE_REG(GYRO_CONFIG, gyro_config | (GYRO_MODE << FS_SEL));

  /* Set accelerometer precision mode */
  uint8_t accel_config = READ_REG(ACCEL_CONFIG);
  accel_config &= ~(0b11 << AFS_SEL); /* sets two AFS_SEL places to 0 */
  WRITE_REG(ACCEL_CONFIG, accel_config | (ACCEL_MODE << AFS_SEL));

  /* Set sample rate divider */
  WRITE_REG(SMPLRT_DIV, IMU_SAMPLE_RATE_DIVIDER);

  /* Configure interrupts to send 50us pulse */
  uint8_t int_pin_cfg = READ_REG(INT_PIN_CFG);
  int_pin_cfg &= ~_BV(LATCH_INT_EN);
  WRITE_REG(INT_PIN_CFG, int_pin_cfg);

  /* Enable data ready interrupts */
  WRITE_REG(FIFO_EN, _BV(XG_FIFO_EN) | _BV(YG_FIFO_EN) | _BV(ZG_FIFO_EN) | _BV(ACCEL_FIFO_EN));
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
