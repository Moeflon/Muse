/*TODO: set AD0 to 0 (logic low)*/
/*TODO PRR0 register bekijken, MSB bepaalt of TWI mogelijk is of niet*/

#include <avr/interrupt.h>
#include <avr/io.h>

#include <util/twi.h>
#include <util/delay.h>

#include <dwenguinoLCD.h>

#include <twiProtocol.h>

#define SLV_I2C_ADDR 0b11010000 //LSB indicates Read/Write; 2nd LSB indicates AD0 set to 0

int main(void) {
  DDRA = 0xFF; // Set all PORTA pins as output
  PORTA = 0; // Turn all LEDs off

  initLCD();
  clearLCD();

  // Start on address
  twi_start(SLV_I2C_ADDR | TWI_READ); //moet TWI_WRITE zijn volgens mij, Slave address moet gegeven
                                      // worden met een WRTIE, register address met READ
  // Write to this register
  twi_write(0x3B);          //3B zijn de hoogste 8bits van het ACCEL_XOUT register, denk dat we hier twi_read moeten doen

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
