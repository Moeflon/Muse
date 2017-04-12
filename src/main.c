#include <dwenguinoLCD.h>
#include <twiProtocol.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include "imuCommunication/imuCommunication.h"
#include "physicsModel/physicsModel.h"

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

  imu_init();
  physicsModel* model = create_model();
  calibrate_gyro(model);
  while(1) {
    update_model_orientation(model);
    printCharToLCD('X', 0, 0);
    printIntToLCD(model->orientation.x, 0, 2); //Print waarden van -16384..16384 (-2g..2g)

    printCharToLCD('Y', 1, 0);
    printIntToLCD(model->orientation.y, 1, 2);

    printCharToLCD('Z', 1, 8);
    printIntToLCD(model->orientation.z, 1, 10);

    _delay_ms(400);
    clearLCD();
  }
}
