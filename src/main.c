#include <avr/interrupt.h>
#include <avr/io.h>

#include <util/twi.h>
#include <util/delay.h>

#include <dwenguinoLCD.h>

#include <twiProtocol.h>

#define SLV_I2C_ADDR 0b11010000 // LSB indicates Read/Write; 2nd LSB indicates AD0 set to 0
#define PWR_MGMT_1 0x6B

int main(void) {
  DDRA = 0xFF; // Set all PORTA pins as output
  PORTA = 0; // Turn all LEDs off
  PRR0 &= ~_BV(PRTWI); // Make sure TWI is enabled in power

  initLCD();
  clearLCD();

  // Set power mode
  twi_write_reg(SLV_I2C_ADDR, PWR_MGMT_1, 0);

  uint8_t data = twi_read_reg(SLV_I2C_ADDR, 0x3C);
  printIntToLCD(data, 0, 0);
}
