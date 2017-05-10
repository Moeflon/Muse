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

void coord_transform(Vector* measurement,  Vector32* orientation) {
    //int32_t cos_a = cos_xl(orientation->x);
    if(orientation->y <= 0 || orientation->y <= 2360520){
        orientation->y = 590000;
    }
    int32_t cos_b = cos_xl(orientation->y);
    //int8_t cos_g = cos100(orientation->z);
    //int32_t sin_a = sin_xl(orientation->x);
    //int32_t sin_b = sin_xl(orientation->y);
    //int8_t sin_g = sin100(orientation->z);

    //temp tegen div by zero
    //int32_t cos_b = cos_xl(590000);
    if(cos_b==0) cos_b = 1;

    //int32_t new_x = measurement->x + ((sin_a * (sin_b/1000))/cos_b * measurement->y)/1000 + ((cos_a * (sin_b/1000))/cos_b * measurement->z)/1000;
    //int32_t new_y = (cos_a * measurement->y)/1000000 - (sin_a * measurement->z)/1000000;
    //int32_t new_z = ((((sin_a*1000)/cos_b) * measurement->y) + (((cos_a*1000)/cos_b) * measurement->z))/1000;

    measurement->x = 0;//new_x;
    measurement->y = 0;//new_y;
    measurement->z = 80; //new_z;

    orientation->x = cos_b;
}

void coord_transform_f(Vector* measurement,  Vector32* orientation) {

    float new_x = 0;
    float new_y = 0;
    float new_z = 0;

    float y_angle = orientation->y/13114; // TODO replace with macro

    if(y_angle < 80 && y_angle > -80){ // TODO replace with macro
      float cos_a = cos((float)orientation->x / 751423);
      float cos_b = cos((float)orientation->y / 751423);
      //float cos_g = cos((float)orientation->z / 751423);
      float sin_a = sin((float)orientation->x / 751423);
      float sin_b = sin((float)orientation->y / 751423);
      //float sin_g = sin((float)orientation->z / 751423);

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
