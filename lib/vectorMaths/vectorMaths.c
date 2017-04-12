/**
 * @file vectorMaths.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include <math.h>
#include "vectorMaths.h"

void add_vector(Vector* a, Vector* b, Vector* dest) {
  dest->x = a->x + b->x;
  dest->y = a->y + b->y;
  dest->z = a->z + b->z;
}

void sub_vector(Vector* a, Vector* b, Vector* dest) {
  dest->x = a->x - b->x;
  dest->y = a->y - b->y;
  dest->z = a->z - b->z;
}

void div_pow_two_vector(uint8_t pow, Vector* a, Vector* dest) {
  dest->x = a->x >> pow;
  dest->y = a->y >> pow;
  dest->z = a->z >> pow;
}

void mul_pow_two_vector(uint8_t pow, Vector* a, Vector* dest) {
  dest->x = a->x << pow;
  dest->y = a->y << pow;
  dest->z = a->z << pow;
}

uint16_t vector_norm(Vector* a) {
  int normsq = ((int)a->x * a->x) + ((int)a->y * a->y) + ((int)a->z * a->z);
  return sqrt(normsq);
}
