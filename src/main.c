#include <dwenguinoLCD.h>
#include <twiProtocol.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include "globals.h"
#include "imuCommunication/imuCommunication.h"
#include "physicsModel/physicsModel.h"
#include "physicsSampler/physicsSampler.h"

volatile state g_state;

int main(void) {
  physicsModel model = { 0 };
  initLCD();
  clearLCD();
  backlightOn();

  imu_init();
  calibrate_imu_data(&model);

  imuDataQueues sampling;
  imuDataQueues processing;
  start_sampler(&sampling, &processing);

  Vector32 orientation;
  for(;;) {
      update_model(&model);
      orientation = model.orientation;
      //sub_from_vector(&orientation, &model.accel_ref);
      //orientation = model.accel_ref;
      shr_vector(10, &orientation);
      div_vector(10, &orientation);

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
