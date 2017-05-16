/**
 * @file globals.h
 * @brief Global variables
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "physicsModel/physicsModel.h"
#include "physicsSampler/physicsSampler.h"
#include "vectorQueue/vectorQueue.h"

/**
 * @brief Global containing pointers to current data queues
 * The interrupt routine uses the sampling queue in this struct to add
 * values to.
 * Processing will swap the pointers and clear the new processing queue
 * such that the interrupt can add to a queue whilst the old one is being processed.
 */
extern volatile dataQueuesPointers g_data_queues_ptrs;

#endif
