/**
 * @file museAPI.h
 * @brief API for move detection
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef MUSE_API_H_
#define MUSE_API_H_

#include <stddef.h>

#include "../physicsModel/physicsModel.h"
#include "../vectorMaths/vectorMaths.h"

/**
 * @brief structure the API user gets access to in each iteration
 */
typedef struct museMotion {
  Vector w; /**> world-axis angular velocity in deg/s */
  Vector a; /**> world-axis acceleration in g */
  Vector v; /**> world-axis velocity in m/s * 64 */
  Vector s; /**> world-axis position in cm */
  Vector o; /**> world-axis orientation in deg * 10 */
} museMotion;

/**
 * @brief Initializes and returns a new, empty physicsModel. Also calibrates device
 * @return an empty physicsModel
 */
physicsModel muse_init(void);

/**
 * @brief Sets up sampling and updates model and calls supplied model
 * The lambda will be called until it returns a non-NULL value or the timout is reached
 * @param timeout the timout in seconds
 * @param model pointer to the physicsModel to update
 * @param lambda uint8_t function pointer to lambda, with museMotion* argument
 * @return return value of the lambda function
 * @retval NULL timeout was reached
 */
uint8_t muse_detect(uint8_t timeout, physicsModel* model, uint8_t (*lambda)(museMotion* m));

/**
 * @brief Updates model and museMotion struct according to new data
 * @param model pointer to the physicsModel to update
 * @param m museMotion struct to store user-accesable data
 */
void muse_update_motion(physicsModel* model, museMotion* m);
#endif
