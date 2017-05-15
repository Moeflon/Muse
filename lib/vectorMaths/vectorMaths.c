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
                   + (((((int32_t)sin_a * sin_b) / cos_b) * body_y) >> TRIG_SHIFT_AMOUNT)
                   + (((((int32_t)cos_a * sin_b) / cos_b) * body_z) >> TRIG_SHIFT_AMOUNT);
  measurement->y = (((int32_t)cos_a * body_y) >> TRIG_SHIFT_AMOUNT)
                   - (((int32_t)sin_a * body_z) >> TRIG_SHIFT_AMOUNT);
  measurement->z = (((int32_t)sin_a * body_y) / cos_b)
                   + (((int32_t)cos_a * body_z) / cos_b);
}

void coord_transform(Vector* measurement,  Vector* orientation){
  int32_t sin_a = lu_sin(orientation->x);
  int32_t sin_b = lu_sin(orientation->y);
  int32_t sin_g = lu_sin(orientation->z);
  int32_t cos_a = lu_cos(orientation->x);
  int32_t cos_b = lu_cos(orientation->y);
  int32_t cos_g = lu_cos(orientation->z);

  int32_t body_x = measurement->x;
  int32_t body_y = measurement->y;
  int32_t body_z = measurement->z;

  // Cache certain calculations
  int32_t cos_g_sin_b_sin_a = (((cos_g*sin_b)>>TRIG_SHIFT_AMOUNT)*sin_a);
  int32_t sin_g_sin_b_sin_a = (((sin_g*sin_b)>>TRIG_SHIFT_AMOUNT)*sin_a);

  measurement->x = (cos_g*cos_b*body_x + sin_g*cos_b*body_y)>>TRIG_SHIFT_AMOUNT  - sin_b*body_z)>>TRIG_SHIFT_AMOUNT;
  measurement->y = ((cos_g_sin_b_sin_a-sin_g*cos_a)*body_x + (sin_g_sin_b_sin_a+cos_g*cos_a)*body_y + cos_b*sin_a*body_z)>>(TRIG_SHIFT_AMOUNT*2);
  measurement->z = ((cos_g_sin_b_sin_a+sin_g*sin_a)*body_x + (sin_g_sin_b_sin_a-cos_g*sin_a)*body_y + cos_b*cos_a*body_z)>>(TRIG_SHIFT_AMOUNT*2);

  /* Unedited transformation formulas, these won't work with scaled sin/cos values
  measurement->x = cos_g*cos_b*body_x + sin_g*cos_b*body_y  - sin_b*body_z;
  measurement->y = (cos_g*sin_b*sin_a-sin_g*cos_a)*body_x + (sin_g*sin_b*sin_a+cos_g*cos_a)*body_y + cos_b*sin_a*body_z;
  measurement->z = (cos_g*sin_b*sin_a+sin_g*sin_a)*body_x + (sin_g*sin_b*sin_a-cos_g*sin_a)*body_y + cos_b*cos_a*body_z;
  */

}
