/**
 * @file globals.h
 * @brief Global variables
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <vectorQueue.h>
#include "physicsModel/physicsModel.h"

/**
 * Global variable for storing model state.
 */
extern volatile physicsModel g_model;

/**
 * Global variables for queues
 */

extern volatile imuQueues g_queues;

/**
 * Global variables and definitions for application state
 */
typedef struct state {
  uint8_t last;
  uint8_t current;
} state;

#define STATE_SET(s) do {                                       \
                          g_state.last = g_state.current;           \
                          g_state.current = (s);                  \
                        } while(0)

#define STATE_RETURN() do {                                     \
                            uint8_t _current = g_state.current;   \
                            g_state.current = state.last;         \
                            g_state.last = _current;              \
                          } while(0)

extern volatile state g_state;

#define MENU 0
#define UPDATE 1

#endif
