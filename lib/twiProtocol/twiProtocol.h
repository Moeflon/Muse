/*
 * twiProtocol.h
 */

#ifndef TWI_PROTOCOL_H_
#define TWI_PROTOCOL_H_

#include <avr/io.h>
#include <util/twi.h>

#define STATUSMASK 0xF8
#define TWI_READ 0x01
#define TWI_WRITE 0x00

/**
 * @brief sends a START to I2C device on address
 * @param address device address appended with mode (READ/WRITE)
 * @return 0: no error
 *         1: start condition acknowledge fail
 *         2: address acknowledge fail
 */
uint8_t twi_start(uint8_t address);

/**
 * @brief sends a STOP to current I2C device
 */
void twi_stop(void);

/**
 * @brief writes data to current connection
 * @param data to be transmitted
 * @return 0: no error
 *         1: data acknowledge fail
 */
uint8_t twi_write(uint8_t data);

/**
 * @brief read data with acknowledgement
 * @return data
 */
uint8_t twi_read_ack(void);

/**
 * @brief read data without acknowledgement
 * @return data
 */
uint8_t twi_read_nack(void);

/**
 * @brief read a register
 * @return 0: no error
 *         1: start condition acknowledge fail
 *         2: address acknowledge fail
 *         3: register write acknowledge fail
 */
uint8_t twi_read_reg(uint8_t slav_addr, uint8_t reg_add);

/**
 * @brief write a register
 * @return 0: no error
 *         1: start condition acknowledge fail
 *         2: address acknowledge fail
 *         3: register write acknowledge fail
 *         4: error whilst writing data
 */
uint8_t twi_write_reg(uint8_t slav_addr, uint8_t reg_addr, uint8_t data);
#endif
