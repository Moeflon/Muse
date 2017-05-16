/**
 * @file physicsSampler.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../imuCommunication/imuCommunication.h"
#include "../globals.h"
#include "../vectorMaths/vectorMaths.h"

#include "physicsSampler.h"

volatile dataQueuesPointers g_data_queues_ptrs;

void swap_data_queues() {
  imuDataQueues* c = g_data_queues_ptrs.processing;
  vq_clear(&c->gyro); /* Clear processing queue for sampling */
  vq_clear(&c->accel);
  g_data_queues_ptrs.processing = g_data_queues_ptrs.sampling;
  g_data_queues_ptrs.sampling = c;
}

void start_sampler(imuDataQueues* q_sampling, imuDataQueues* q_processing) {
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
  vq_clear(&q_processing->gyro);
  vq_clear(&q_processing->accel);
  vq_clear(&q_sampling->gyro);
  vq_clear(&q_sampling->accel);

  /* Set global pointers for interrupt routine */
  g_data_queues_ptrs.processing = q_processing;
  g_data_queues_ptrs.sampling = q_sampling;
}

void stop_sampler() {
  imu_uninit_sampling();
  EIMSK &= ~_BV(INT3); /* Disable INT3 interrupts */
}

ISR(INT3_vect) {
  imuDataQueues* s = g_data_queues_ptrs.sampling;
  if(vq_free_space(&s->accel) < 10) {
    STATE_SET(UPDATE);
  }

  vq_enqueue(imu_get_angular(), &s->gyro);
  vq_enqueue(imu_get_acceleration(), &s->accel);
}
