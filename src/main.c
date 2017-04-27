#include <dwenguinoLCD.h>
#include <twiProtocol.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include "imuCommunication/imuCommunication.h"
#include "physicsModel/physicsModel.h"
#include "physicsSampler/physicsSampler.h"

/* Originally declared in physicsSampler/physicsSampler.h */
extern volatile physicsModel g_model;

int main(void) {
  static physicsModel model;

  initLCD();
  clearLCD();
  backlightOn();

  imu_init();

  model = g_model;
  calibrate_gyro(&model);
  g_model = model;

  start_sampler();

  for(;;) {
      Vector orientation = g_model.orientation;
      clearLCD();
      printCharToLCD('X', 0, 0);
      printIntToLCD(orientation.x, 0, 2);

      printCharToLCD('Y', 1, 0);
      printIntToLCD(orientation.y, 1, 2);

      printCharToLCD('Z', 1, 8);
      printIntToLCD(orientation.z, 1, 10);
      _delay_ms(100);
  }
}
