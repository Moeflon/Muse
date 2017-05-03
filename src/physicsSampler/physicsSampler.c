/**
 * @file physicsSampler.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include <vectorMaths.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <dwenguinoLCD.h>

#include "../imuCommunication/imuCommunication.h"
#include "../globals.h"
#include "physicsSampler.h"

void start_sampler() {
  imu_init_sampling();
  
  // PD3 has to be input and pullup to act as INT3
  DDRD &= ~_BV(DDD3);
  PORTD |= ~_BV(PORTD3);

  SREG |= _BV(SREG_I);
  EIMSK &= ~_BV(INT3); /* Disable INT3 interrupts */

  /* Rising edge of INT3 generates interrupt */
  EICRA |= _BV(ISC31);
  EICRA |= _BV(ISC30);

  EIMSK |= _BV(INT3); /* Enable INT0 interrupts */
}

void stop_sampler() {
  EIMSK &= ~_BV(INT3); /* Disable INT3 interrupts */
}

ISR(INT3_vect) {
  if(vq_free_space(&g_gyro_queue) < 10) {
    STATE_SET(UPDATE);
  }

  vq_enqueue(imu_get_angular(), &g_gyro_queue);
  vq_enqueue(imu_get_acceleration(), &g_accel_queue);
}
