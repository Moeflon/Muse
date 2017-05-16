#include <math.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

#include "dwenguinoLCD/dwenguinoLCD.h"
#include "globals.h"
#include "imuCommunication/imuCommunication.h"
#include "physicsModel/physicsModel.h"
#include "physicsSampler/physicsSampler.h"
#include "twiProtocol/twiProtocol.h"

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

      clearLCD();
      printCharToLCD('X', 0, 0);
      printIntToLCD(print_val.x >> 8, 0, 2);

      printCharToLCD('Y', 1, 0);
      printIntToLCD(print_val.y >> 8, 1, 2);

      printCharToLCD('Z', 1, 8);
      printIntToLCD(print_val.z >> 8, 1, 10);
      _delay_ms(100);
  }
}
