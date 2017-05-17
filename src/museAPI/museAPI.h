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

typedef struct museMotion {
  Vector v;
  Vector s;
  Vector o;
} museMotion;

physicsModel muse_init(void);
uint8_t muse_detect(uint8_t timeout, physicsModel* model, uint8_t (*lambda)(museMotion* m));
void muse_update_motion(physicsModel* model, museMotion* m);
#endif
