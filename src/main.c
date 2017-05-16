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

  volatile imuDataQueues sampling = { 0 };
  volatile imuDataQueues processing = { 0 };
  start_sampler(&sampling, &processing);

  Vector32 print_val;
  for(;;) {
      update_model(&model);
      print_val = model.position_raw;
      //sub_from_vector(&orientation, &model.accel_ref);
      //orientation = model.accel_ref;
      //shr_vector(10, &orientation);
      //div_vector(10, &orientation);

      clearLCD();
      printCharToLCD('X', 0, 0);
      printIntToLCD(print_val.x >> 2, 0, 2);

      printCharToLCD('Y', 1, 0);
      printIntToLCD(print_val.y >> 2, 1, 2);

      printCharToLCD('Z', 1, 8);
      printIntToLCD(print_val.z >> 2, 1, 10);
      _delay_ms(100);
  }
}
