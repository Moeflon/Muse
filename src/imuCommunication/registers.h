/**
 * @file registers.h
 * @brief Relevant IMU register mappings
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef IMU_REGISTERS_H_
#define IMU_REGISTERS_H_

#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define SMPLRT_DIV 0x19
#define FIFO_EN 0x23
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38

#define TEMP_FIFO_EN 7
#define INT_LEVEL 7
#define INT_RD_CLEAR 4
#define LATCH_INT_EN 5
#define XG_FIFO_EN 6
#define YG_FIFO_EN 5
#define ZG_FIFO_EN 4
#define ACCEL_FIFO_EN 3
#define FS_SEL 3
#define AFS_SEL 3
#define DATA_RDY_EN 0

/* Macros so we don't always have to supply our slave address */
#define SLV_TWI_ADDR 0b11010000 /* LSB indicates Read/Write; 2nd LSB indicates AD0 */
#define WRITE_REG(r, d) twi_write_reg(SLV_TWI_ADDR, r, d)
#define READ_REG(r) twi_read_reg(SLV_TWI_ADDR, r)

#endif
