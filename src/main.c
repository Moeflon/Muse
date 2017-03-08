#include <avr/interrupt.h>
#include <avr/io.h>

#include <util/twi.h>
#include <util/delay.h>

#include <dwenguinoLCD.h>

#include <twiProtocol.h>

#include <math.h>
#define PI 3.1415

#define SLV_I2C_ADDR 0b11010000 // LSB indicates Read/Write; 2nd LSB indicates AD0 set to 0
#define PWR_MGMT_1 0x6B

int parser(uint8_t, uint8_t);

int parser(uint8_t high, uint8_t low){
  int16_t result;
  result |= low;
  result |= (high<<8);
  return result;
}


int main(void) {
  DDRA = 0xFF; // Set all PORTA pins as output
  PORTA = 0; // Turn all LEDs off
  PRR0 &= ~_BV(PRTWI); // Make sure TWI is enabled in power

  initLCD();
  clearLCD();
  backlightOn();

  // Set power mode
  twi_write_reg(SLV_I2C_ADDR, PWR_MGMT_1, 0);

  /*vicignore*/
  uint8_t x_low = twi_read_reg(SLV_I2C_ADDR, 0x3C);
  uint8_t x_high = twi_read_reg(SLV_I2C_ADDR, 0x3B);
  uint16_t x = parser(x_high, x_low);

  uint8_t y_low = twi_read_reg(SLV_I2C_ADDR, 0x3E);
  uint8_t y_high = twi_read_reg(SLV_I2C_ADDR, 0x3D);
  uint16_t y = parser(y_high, y_low);

  uint8_t z_low = twi_read_reg(SLV_I2C_ADDR, 0x40);
  uint8_t z_high = twi_read_reg(SLV_I2C_ADDR, 0x3F);
  uint16_t z = parser(z_high, z_low);

  printCharToLCD('X', 0, 0);
  printIntToLCD(x, 0, 2); //Print waarden van -16384..16384 (-2g..2g)

  printCharToLCD('Y', 1, 0);
  printIntToLCD(y, 1, 2);

  printCharToLCD('Z', 1, 8);
  printIntToLCD(z, 1, 10);

  double beta = atan( ((double)x) / ((double)z) );
  printCharToLCD('B', 0, 8);
  printIntToLCD((int) (beta*180/PI), 0, 10);
}
