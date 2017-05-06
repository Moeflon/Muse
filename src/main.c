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

volatile physicsModel g_model;
volatile imuQueues g_queues;
volatile state g_state;

int main(void) {
  static physicsModel model;

  initLCD();
  clearLCD();
  backlightOn();

  imu_init();

  calibrate_gyro(&model);
  g_model = model;

  start_sampler();
  Vectorf orientation;
  for(;;) {
      update_model(&g_queues, &g_model);
      orientation = quat_to_euler(&g_model.orientation);
      //div_vector(ORIENTATION_UNITS_DEG, &orientation);

      clearLCD();
      printCharToLCD('X', 0, 0);
      printIntToLCD(orientation.x * 100, 0, 2);

      printCharToLCD('Y', 1, 0);
      printIntToLCD(orientation.y * 100, 1, 2);

      printCharToLCD('Z', 1, 8);
      printIntToLCD(orientation.z * 100, 1, 10);
      _delay_ms(10);
  }
}
