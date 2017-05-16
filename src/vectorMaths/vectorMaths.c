/**
 * @file vectorMaths.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include "vectorMaths.h"

void euler_transform(Vector* measurement,  Vector* orientation) {
  int16_t sin_a = lu_sin(orientation->x);
  int16_t sin_b = lu_sin(orientation->y);
  int16_t cos_a = lu_cos(orientation->x);
  int16_t cos_b = lu_cos(orientation->y);

  int16_t body_x = measurement->x;
  int16_t body_y = measurement->y;
  int16_t body_z = measurement->z;

  /** @see http://www.chrobotics.com/library/understanding-euler-angles */
  /* Order of trig operations was deliberately changed to facilitate fixed point by shifting */
  measurement->x = body_x
                   + (((((int32_t)sin_a * sin_b) / cos_b) * body_y) >> TRIG_SHIFT)
                   + (((((int32_t)cos_a * sin_b) / cos_b) * body_z) >> TRIG_SHIFT);
  measurement->y = (((int32_t)cos_a * body_y) >> TRIG_SHIFT)
                   - (((int32_t)sin_a * body_z) >> TRIG_SHIFT);
  measurement->z = (((int32_t)sin_a * body_y) / cos_b)
                   + (((int32_t)cos_a * body_z) / cos_b);
}
