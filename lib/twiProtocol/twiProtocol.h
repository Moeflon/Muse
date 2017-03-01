#include <avr/io.h>
#include <util/twi.h>

#define STATUSMASK 0xF8
#define TWI_READ 0x01
#define TWI_WRITE 0x00

/**
 * @brief sends a START to I2C device on address
 * @param address device address appended with mode (READ/WRITE)
 *
 */
uint8_t twi_start(uint8_t address);

/**
 * @brief sends a STOP to current I2C device
 */
void twi_stop(void);

/**
 * @brief writes data to current connection
 * @param c data to be transmitted
 */
uint8_t twi_write(uint8_t data);

/**
 * @brief read data with acknowledgement
 */
uint8_t twi_read_ack(void);

/**
 * @brief read data without acknowledgement
 */
uint8_t twi_read_nack(void);
