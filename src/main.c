#include <dwenguinoLCD.h>
#include <twiProtocol.h>
#include <imuCommunication.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

#define PI 3.1415

int parser(uint8_t, uint8_t);

int parser(uint8_t high, uint8_t low){
  int16_t result;
  result |= low;
  result |= (high << 8);
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
  WRITE_REG(PWR_MGMT_1, 0);

  while(1) {
    clearLCD();

    Vector accel = imu_get_acceleration();

    printCharToLCD('X', 0, 0);
    printIntToLCD(accel.x, 0, 2); //Print waarden van -16384..16384 (-2g..2g)

    printCharToLCD('Y', 1, 0);
    printIntToLCD(accel.y, 1, 2);

    printCharToLCD('Z', 1, 8);
    printIntToLCD(accel.z, 1, 10);

    double beta = atan( ((double)accel.x) / ((double)accel.z) );
    printCharToLCD('B', 0, 8);
    printIntToLCD((int) (beta*180/PI), 0, 10);

    _delay_ms(200);
  }
}
