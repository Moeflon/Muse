/**
 * @file physicsSampler.h
 * @brief Declares functions to sample accelerometer & gyro data
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef PHYSICS_SAMPLER_H_
#define PHYSICS_SAMPLER_H_

#include <stdint.h>
#include "../physicsModel/physicsModel.h"

#define TIMER1_PRESCALER_64 3
#define TIMER1_TICKS_PER_MS_P64 250

/* See paper for explanation, these two need to mutiply together to 1024 */
#define SAMPLE_PERIOD_MS 8
#define GYRO_FACTOR_DENOM 128

/* Global variable for storing model state.
   Reference in other files with 'extern volatile physicsModel g_model'.
   Is volatile because it is altered in interrupts. And can thus change outside of the normal flow of execution, making
   certain optimizations dangerous. Volatile refrains the compiler from applying these optimizations. */
volatile physicsModel g_model;

/**
 * @brief Sets necessary registers for enabling timer1
 */
void start_sampler(void);

/**
 * @brief Sets necessary registers for disabling timer1
 */
void stop_sampler(void);

/**
 * @brief adjusts orientation vector according to new measurement
 * @param model pointer to model
 */
void update_model_orientation(physicsModel* model);

/**
 * @brief adjusts position vector according to new measurement
 * @param model pointer to model Vector
 */
void update_model_position(physicsModel* model);


#endif
