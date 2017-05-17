/**
 * @file museAPI.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include <time.h>

#include "../imuCommunication/imuCommunication.h"
#include "../physicsSampler/physicsSampler.h"

#include "museAPI.h"

physicsModel muse_init(void) {
  physicsModel model = { 0 };

  imu_init();
  calibrate_imu_data(&model);

  return model;
}

uint8_t muse_detect(uint8_t timeout,
                    physicsModel* model,
                    uint8_t (*lambda)(museMotion* m)) {
  time_t start = time(NULL);

  museMotion m = { 0 };

  volatile imuDataQueues one = { 0 };
  volatile imuDataQueues two = { 0 };
  start_sampler(&one, &two);

  while((time(NULL) - start) < timeout) {
    muse_update_motion(model, &m);
    uint8_t ret = lambda(&m);

    if(ret != NULL) {
      stop_sampler();
      zero_model_accel(model);
      return ret;
    }
  }

  stop_sampler();
  zero_model_accel(model);
  return NULL;
}

void muse_update_motion(physicsModel* model, museMotion* m) {
  update_model(model);
  m->v = model->velocity_m_s;

  Vector32 s = model->position_raw;
  shr_vector(POSITION_CM_SHIFT, &s);

  m->s.x = s.x;
  m->s.y = s.y;
  m->s.z = s.z;
  
  m->o = model->orientation_deg;
}
