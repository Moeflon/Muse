#include "twiProtocol.h"

uint8_t twi_start(uint8_t address) {
  // Transmit START
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);

  // Wait for end of transmission
  while(!(TWCR & _BV(TWINT)));

  // Check if start was received
  if((TWSR & STATUSMASK) != TW_START) { return 1; }

  // Load address into data register
  TWDR = address;

  // Prepare for transmission of address
  TWCR = _BV(TWINT) | _BV(TWEN);

  // Wait for end of transmission
  while(!(TWCR & _BV(TWINT)));

  // Check if the device has acknowledged the mode
  uint8_t twst = TW_STATUS & STATUSMASK;
  if((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

  return 0;
}

void twi_stop(void) {
  // Transmit STOP
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);

  // Wait for end of transmission
  while(!(TWCR & _BV(TWINT)));
}

uint8_t twi_write(uint8_t data) {
  // Load data into data register
  TWDR = data;

  // Prepare for transmission of data
  TWCR = _BV(TWINT) | _BV(TWEN);

  // Wait for end of transmission
  while(!(TWCR & _BV(TWINT)));

  // Check if device has acknowledged the data
  if((TWSR & STATUSMASK) != TW_MT_DATA_ACK) { return 1; }

  return 0;
}

uint8_t twi_read_ack(void){
	// Enable TWI and set acknowledge
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);

  // Wait for end of transmission
  while(!(TWCR & _BV(TWINT)));

	// Return data
	return TWDR;
}

uint8_t twi_read_nack(void){
	// Enable TWI and don't set acknowledge
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);

  // Wait for end of transmission
  while(!(TWCR & _BV(TWINT)));

	// Return data
	return TWDR;
}
