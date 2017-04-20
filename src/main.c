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

extern physicsModel g_model;

int main(void) {
  initLCD();
  clearLCD();
  backlightOn();

  imu_init();
  calibrate_gyro(&g_model);
  init_ddi_buffer(&g_model.gyro_ddi, imu_get_angular);
  start_sampler();

  for(;;) {
      clearLCD();
      printCharToLCD('X', 0, 0);
      printIntToLCD(g_model.orientation.x, 0, 2);

      printCharToLCD('Y', 1, 0);
      printIntToLCD(g_model.orientation.y, 1, 2);

      printCharToLCD('Z', 1, 8);
      printIntToLCD(g_model.orientation.z, 1, 10);
      _delay_ms(100);
  }
}
