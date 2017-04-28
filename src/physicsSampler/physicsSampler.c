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

/* Originally declared in globals.h */
extern volatile physicsModel g_model;
extern volatile vectorQueue g_gyro_queue;
extern volatile vectorQueue g_accel_queue;

void start_sampler() {
  SREG |= _BV(SREG_I);
  EIMSK &= ~_BV(INT0); /* Disable INT0 interrupts */

  /* Rising edge of INT0 generates interrupt */
  EICRA |= _BV(ISC01);
  EICRA |= _BV(ISC00);

  EIMSK |= _BV(INT0); /* Enable INT0 interrupts */
}

void stop_sampler() {
  EIMSK &= ~_BV(INT0); /* Disable INT0 interrupts */
}

ISR(INT0_vect) {
  if(vq_free_space(&g_gyro_queue) < 10) {
    SET_STATE(UPDATE);
  }

  Vector angular = imu_get_angular();
  vq_enqueue(&angular, &g_gyro_queue);

  Vector accel = imu_get_acceleration();
  vq_enqueue(&accel, &g_accel_queue));
}
