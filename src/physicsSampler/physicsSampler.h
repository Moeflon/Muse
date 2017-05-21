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
#include "../vectorQueue/vectorQueue.h"

/**
 * @brief Queues used for storing and processing sampled data
 */
typedef struct imuDataQueues {
  vectorQueue gyro;
  vectorQueue accel;
} imuDataQueues;

/**
 * @brief Struct around processing and sampling queuePointers for dynamic switching
 * @note These queues are always in memory to avoid memcpy and malloc when returning a sample queue to
 * a processing function.
 */
typedef struct dataQueuesPointers {
  imuDataQueues* sampling;
  imuDataQueues* processing;
} dataQueuesPointers;

/**
 * @brief Global containing pointers to current data queues
 * The interrupt routine uses the sampling queue in this struct to add
 * values to.
 * Processing will swap the pointers and clear the new processing queue
 * such that the interrupt can add to a queue whilst the old one is being processed.
 */
extern volatile dataQueuesPointers g_data_queues_ptrs;

/**
 * @brief Swaps the sampling and processing dataQueuesPointers
 *        so the interrupt can update a fresh dataQueue while
 *        we processes the old queue
 */
void swap_data_queues(void);

/**
 * @brief Sets necessary registers for enabling timer1
 * @queues q_sampling pointer imuDataQueues initially used for sampling
 * @queues q_processing pointer imuDataQueues initially used for processing
 */
void start_sampler(imuDataQueues* q_sampling, imuDataQueues* q_processing);

/**
 * @brief Sets necessary registers for disabling timer1
 */
void stop_sampler(void);

#endif
