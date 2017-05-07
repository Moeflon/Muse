/**
 * @file quaternionMath.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include <math.h>
#include "quaternionMaths.h"

float quat_norm(Quaternion32* q) {
  return sqrtf(q->w*q->w + q->x*q->x + q->y*q->y + q->z*q->z);
}

void normalize_quat(Quaternion32* q) {
  float norm = quat_norm(q);
  q->w /= norm;
  q->x /= norm;
  q->y /= norm;
  q->z /= norm;
}

Vectorf quat_to_euler(Quaternion32* q) {
  Vectorf euler;
  /* Deze omzettingsformules kloppen niet echt */
  float test = q->x * q->y + q->z * q->w;
	if(test > 0.499) { /* singularity at north pole */
		euler.x = 2 * atan2(q->x, q->w);
		euler.y = M_PI_2;
		euler.z = 0;
	}
	else if(test < -0.499) { /* singularity at south pole */
		euler.x = -2 * atan2(q->x, q->w);
		euler.x = -M_PI_2;
		euler.x = 0;
	}
  else {
    float sqx = q->x * q->x;
    float sqy = q->y * q->y;
    float sqz = q->z * q->z;

    euler.x = atan2(2*q->y * q->w - 2*q->x * q->z, 1 - 2*sqy - 2*sqz);
    euler.y = asin(2*test);
    euler.z = atan2(2*q->x * q->w - 2*q->y * q->z , 1 - 2*sqx - 2*sqz);
  }

  return euler;
}
