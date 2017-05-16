/**
 * @file twiProtocol.h
 * @brief Functions for accessing TWI devices
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef TWI_PROTOCOL_H_
#define TWI_PROTOCOL_H_

#include <avr/io.h>
#include <util/twi.h>

#define STATUSMASK 0xF8
#define TWI_READ 0x01
#define TWI_WRITE 0x00

/**
 * @brief Sends a START to I2C device on address
 * @param address device address appended with mode (READ/WRITE)
 * @retval 0 no error
 * @retval 1 start condition acknowledge fail
 * @retval 2 address acknowledge fail
 */
uint8_t twi_start(uint8_t address);

/**
 * @brief Sends a STOP to current I2C device
 */
void twi_stop(void);

/**
 * @brief Writes data to current connection
 * @param data to be transmitted
 * @retval 0 no error
 * @retval 1 data acknowledge fail
 */
uint8_t twi_write(uint8_t data);

/**
 * @brief Read data with acknowledgement
 * @return data
 */
uint8_t twi_read_ack(void);

/**
 * @brief Read data without acknowledgement
 * @return data
 */
uint8_t twi_read_nack(void);

/**
 * @brief Read a register
 * @param slav_addr slave address
 * @param reg_addr slave register address
 * @retval 0 no error
 * @retval 1 start condition acknowledge fail
 * @retval 2 address acknowledge fail
 * @retval 3 register write acknowledge fail
 */
uint8_t twi_read_reg(uint8_t slav_addr, uint8_t reg_add);

/**
 * @brief Write a register
 * @param slav_addr slave address
 * @param reg_addr slave register address
 * @param data to be transmitted
 * @retval 0 no error
 * @retval 1 start condition acknowledge fail
 * @retval 2 address acknowledge fail
 * @retval 3 register write acknowledge fail
 * @retval 4 error whilst writing data
 */
uint8_t twi_write_reg(uint8_t slav_addr, uint8_t reg_addr, uint8_t data);
#endif
