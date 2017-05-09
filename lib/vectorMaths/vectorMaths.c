/**
 * @file vectorMaths.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include "trig.h"
#include <math.h>
#include "vectorMaths.h"

int32_t vector_norm_squared(Vector* v){
  return (int32_t) v->x*v->x + v->y*v->y + v->z*v->z;
}

void coord_transform(Vector* measurement,  Vector* orientation) {
    int8_t cos_a = cos100(orientation->x);
    int8_t cos_b = cos100(orientation->y);
    int8_t cos_g = cos100(orientation->z);
    int8_t sin_a = sin100(orientation->x);
    int8_t sin_b = sin100(orientation->y);
    int8_t sin_g = sin100(orientation->z);

    int32_t new_x = (cos_b * cos_g * (int32_t)measurement->x) + (sin_b * cos_g * (int32_t)measurement->z) - (sin_g * 100 * (int32_t)measurement->y);
    int32_t new_y = (sin_g * cos_b * (int32_t)measurement->x) + (cos_g * cos_a * (int32_t)measurement->y) - (sin_a * 100 * (int32_t)measurement->z);
    int32_t new_z = (sin_a * cos_g * (int32_t)measurement->y) + (cos_a * cos_b * (int32_t)measurement->z) - (sin_b * 100 * (int32_t)measurement->x);

    measurement->x = new_x / 10000;
    measurement->y = new_y / 10000;
    measurement->z = new_z / 10000;
}

void coord_transform_f(Vector* measurement,  Vector32* orientation) {

    float new_x = 0;
    float new_y = 0;
    float new_z = 0;

    float y_angle = orientation->y/13114; // TODO replace with macro

    if(y_angle < 70 && y_angle > -70){ // TODO replace with macro
      float cos_a = cos((float)orientation->x / 751423);
      float cos_b = cos((float)orientation->y / 751423);
      float cos_g = cos((float)orientation->z / 751423);
      float sin_a = sin((float)orientation->x / 751423);
      float sin_b = sin((float)orientation->y / 751423);
      float sin_g = sin((float)orientation->z / 751423);

      new_x = measurement->x + (sin_a * (sin_b/cos_b) * measurement->y) + (cos_a * (sin_b/cos_b) * measurement->z);
      new_y = (cos_a * measurement->y) - (sin_a * measurement->z);
      new_z = ((sin_a/cos_b) * measurement->y) + ((cos_a/cos_b) * measurement->z);
    } else {

      float cos_a = cos((float)orientation->x / 751423);
       new_y = cos_a * measurement->y;
    }

    if(new_x > 32768 || new_z > 32768){
      new_x = 0;
      new_z = 0;
    }

    measurement->x = new_x;
    measurement->y = new_y;
    measurement->z = new_z;
}
