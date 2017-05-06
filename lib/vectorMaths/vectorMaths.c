/**
 * @file vectorMaths.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include "trig.h"
#include <math.h>
#include "vectorMaths.h"

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
    float cos_a = cos((float)orientation->x / 751423);
    float cos_b = cos((float)orientation->y / 751423);
    float cos_g = cos((float)orientation->z / 751423);
    float sin_a = sin((float)orientation->x / 751423);
    float sin_b = sin((float)orientation->y / 751423);
    float sin_g = sin((float)orientation->z / 751423);

    float new_x = measurement->x + (sin_a * (sin_b/cos_b) * measurement->y) + (cos_a * (sin_b/cos_b) * measurement->z);
    float new_y = (cos_a * measurement->y) - (sin_a * measurement->z);
    float new_z = ((sin_a/cos_b) * measurement->y) + ((cos_a/cos_b) * measurement->z);

    measurement->x = new_x;
    measurement->y = new_y;
    measurement->z = new_z;
}
