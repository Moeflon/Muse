#include <avr/interrupt.h>
#include <avr/io.h>

#include <util/twi.h>
#include <util/delay.h>

#include <dwenguinoLCD.h>

#include <twiProtocol.h>

int main(void) {
  DDRA = 0xFF; // Set all PORTA pins as output
  PORTA = 0; // Turn all LEDs off

  initLCD();
  clearLCD();

  // Start on address
  twi_start(0b11010000 | TWI_READ);

  // Write to this register
  twi_write(0x3B);

  // Receive data
  uint8_t data = twi_read_nack();

  // Send stop
  twi_stop();

  /**
   * TODO:
   * - duplicate transmit and receive (register) function
   * - https://github.com/g4lvanix/I2C-master-lib/blob/master/i2c_master.c
   */
}

void error(void) {
  // Crash
}
