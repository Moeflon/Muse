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

/* Global model variable */
static physicsModel model;

int main(void) {
  DDRA = 0xFF; // Set all PORTA pins as output
  PORTA = 0; // Turn all LEDs off
  PRR0 &= ~_BV(PRTWI); // Make sure TWI is enabled in power

  initLCD();
  clearLCD();
  backlightOn();

  imu_init();
  calibrate_gyro(&model);

  Vector values[3];
  values[0] = imu_get_angular();
  values[1] = imu_get_angular();
  values[2] = imu_get_angular();
  init_ddi_buffer(&model.gyro_ddi, values);

  while(1) {
    update_model_orientation(&model);
    printCharToLCD('X', 0, 0);
    printIntToLCD(model.orientation.x, 0, 2); //Print waarden van -16384..16384 (-2g..2g)

    printCharToLCD('Y', 1, 0);
    printIntToLCD(model.orientation.y, 1, 2);

    printCharToLCD('Z', 1, 8);
    printIntToLCD(model.orientation.z, 1, 10);

    _delay_ms(400);
    clearLCD();
  }
}
