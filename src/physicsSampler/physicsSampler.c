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
#include "physicsSampler.h"

/* Originally declared in physicsSampler/physicsSampler.h */
extern volatile physicsModel g_model;

void start_sampler() {
  SREG |= _BV(SREG_I);
  TIMSK1 &= ~_BV(OCIE1A); /* Disable interrupts */
  OCR1A = TIMER1_TICKS_PER_MS_P64 * SAMPLE_PERIOD_MS; /* Set value that triggers interrupt */
  TCCR1A = 0; /* Set CTC mode */
  TCCR1B = TIMER1_PRESCALER_64 | _BV(WGM12); /* Set prescaler */
  TCNT1 = 0; /* Reset count register */
  TIMSK1 |= _BV(OCIE1A); /* Enable interrupts */
}

void stop_sampler() {
  TCCR1B = 0;
}

void update_model_orientation(physicsModel* model) {
  Vector angular = imu_get_angular();
  normalize_angular(&angular, model);
  div_scal_vector(GYRO_FACTOR_DENOM, &angular, &angular);
  add_vector(&angular, &model->orientation, &model->orientation);
}

ISR(TIMER1_COMPA_vect) {
  /* Cache global model in local variable for faster execution */
  physicsModel model = g_model;

  update_model_orientation(&model);

  /* Update global variable */
  g_model = model;
}
