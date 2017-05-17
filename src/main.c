#include <math.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

#include "dwenguinoLCD/dwenguinoLCD.h"
#include "globals.h"
#include "imuCommunication/imuCommunication.h"
#include "physicsModel/physicsModel.h"
#include "physicsModel/printModel.h"
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
  Vector32 v;
  char* s = "POS";

  for(;;) {
      update_model(&model);
      v = model.position_raw;
      //printModel(&model, 0);

      clearLCD();
      printCharToLCD('X', 0, 0);
      printIntToLCD(v.x >> 8, 0, 2);

      printCharToLCD('Y', 1, 0);
      printIntToLCD(v.y >> 8, 1, 2);

      printCharToLCD('Z', 1, 8);
      printIntToLCD(v.z >> 8, 1, 10);

      for(uint8_t i = 0; i < 3; i++){
      printCharToLCD(*(s+i), 0, 8+i);
      }
      _delay_ms(100); // simulates API user's code
  }
}
