/**
 * @file physicsSampler.h
 * @brief Declares functions to sample accelerometer & gyro data
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef PHYSICS_SAMPLER_H_
#define PHYSICS_SAMPLER_H_

#include <stdint.h>
#include <vectorQueue.h>

#include "../physicsModel/physicsModel.h"

/**
 * @brief Sets necessary registers for enabling timer1
 */
void start_sampler(void);

/**
 * @brief Sets necessary registers for disabling timer1
 */
void stop_sampler(void);

#endif
