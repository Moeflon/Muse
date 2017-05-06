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

  /* PD3 has to be input and pullup to act as INT3 */
  DDRD &= ~_BV(DDD3);
  PORTD |= ~_BV(PORTD3);

  SREG |= _BV(SREG_I);
  EIMSK &= ~_BV(INT3); /* Disable INT3 interrupts */

  /* Rising edge of INT3 generates interrupt */
  EICRA |= _BV(ISC31);
  EICRA |= _BV(ISC30);

  EIMSK |= _BV(INT3); /* Enable INT0 interrupts */

  /* Initialize sample and processing queues for sampling */
  g_queues.gyro_sample_ptr = &g_queues.one;
  g_queues.gyro_processing_ptr = &g_queues.two;
  g_queues.accel_sample_ptr = &g_queues.three;
  g_queues.accel_processing_ptr = &g_queues.four;
  vq_clear(g_queues.gyro_sample_ptr);
  vq_clear(g_queues.accel_sample_ptr);
}

void stop_sampler() {
  imu_uninit_sampling();
  EIMSK &= ~_BV(INT3); /* Disable INT3 interrupts */
}

ISR(INT3_vect) {
  if(vq_free_space(g_queues.accel_sample_ptr) < 10) {
    STATE_SET(UPDATE);
  }

  vq_enqueue(imu_get_angular(), g_queues.gyro_sample_ptr);
  vq_enqueue(imu_get_acceleration(), g_queues.accel_sample_ptr);
}
