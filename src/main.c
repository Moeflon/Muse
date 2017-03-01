#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/twi.h>

#include <util/delay.h>

#include <dwenguinoLCD.h>
#define STATUSMASK 0xF8

// https://github.com/g4lvanix/I2C-master-lib/blob/master/i2c_master.c
uint8_t send_start(uint8_t address) {
  // Start condition
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);

  // Wait for end of transmission
  while(!(TWCR & _BV(TWINT)));

  // Check if start was received
  if((TWSR & STATUSMASK) != TW_START) { return 1 };

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

uint8_t set_write(unsigned char address) {
  TWDR = (address << 1) + 0; // Write mode
  TWCR = _BV(TWINT) | _BV(TWEN); // Clear TWINT, Enable TWI
  while(!(TWCR & _BV(TWINT))); // Wait for acknowledge
  if((TWSR & STATUSMASK) != TW_MT_SLA_ACK) return 1;
  return 1;
}

uint8_t set_read(unsigned char address) {
  TWDR = (address << 1) + 1; // Read mode
  TWCR = _BV(TWINT) | _BV(TWEN); // Clear TWINT, Enable TWI
  while(!(TWCR & _BV(TWINT))); // Wait for acknowledge
  if((TWSR & STATUSMASK) != TW_MR_SLA_ACK) return 0;
  return 1;
}

uint8_t send_data(unsigned char data) {
  TWDR = data;
  TWCR = _BV(TWINT) | _BV(TWEN);
  while(!(TWCR & _BV(TWINT)));
  if((TWSR & STATUSMASK) != TW_MT_DATA_ACK) return 0;
  return 0;
}

int main(void) {
  DDRA = 0xFF; // Set all PORTA pins as output
  PORTA = 0; // Turn all LEDs off

  initLCD();
  clearLCD();

  send_start();
  //send_write();
  send_data(0x3B);
}

void send_stop(void) {
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

void error(void) {
  // Crash
}
