/**
 * @file vectorMaths.h
 * @brief Simple vector struct and vector operation definitions
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef VECTOR_MATHS_H_
#define VECTOR_MATHS_H_

#include <stdint.h>

/**
 * @brief A simple three-dimensional vector
 */
typedef struct Vector {
  int16_t x; /**> x component */
  int16_t y; /**> y component */
  int16_t z; /**> z component */
} Vector;

/**
 * @brief A 32-bit three-dimensional vector
 */
typedef struct Vector32 {
  int32_t x; /**> x component */
  int32_t y; /**> y component */
  int32_t z; /**> z component */
} Vector32;

/**
 * @brief A floating point three-dimensional vector
 */
typedef struct Vectorf {
  float x; /**> x component */
  float y; /**> y component */
  float z; /**> z component */
} Vectorf;

#define clear_vector(a) do {        \
  (a)->x = 0;                       \
  (a)->y = 0;                       \
  (a)->z = 0;                       \
} while(0)

#define add_vectors(a, b, c) do {   \
  (c)->x = (a)->x + (b)->x;         \
  (c)->y = (a)->y + (b)->y;         \
  (c)->z = (a)->z + (b)->z;         \
} while(0)

#define sub_vectors(a, b, c) do {   \
  (c)->x = (a)->x - (b)->x;         \
  (c)->y = (a)->y - (b)->y;         \
  (c)->z = (a)->z - (b)->z;         \
} while(0)

#define add_to_vector(a, b) do {   \
  (a)->x += (b)->x;                \
  (a)->y += (b)->y;                \
  (a)->z += (b)->z;                \
} while(0)

#define sub_from_vector(a, b) do { \
  (a)->x -= (b)->x;                \
  (a)->y -= (b)->y;                \
  (a)->z -= (b)->z;                \
} while(0)

#define div_vectors(s, a, b) do {  \
  (b)->x = (a)->x / (s);           \
  (b)->y = (a)->y / (s);           \
  (b)->z = (a)->z / (s);           \
} while(0)

#define mul_vectors(s, a, b) do {  \
  (b)->x = (a)->x * (s);           \
  (b)->y = (a)->y * (s);           \
  (b)->z = (a)->z * (s);           \
} while(0)

#define div_vector(s, a) do {      \
  (a)->x /= (s);                   \
  (a)->y /= (s);                   \
  (a)->z /= (s);                   \
} while(0)

#define mul_vector(s, a) do {      \
  (a)->x *= (s);                   \
  (a)->y *= (s);                   \
  (a)->z *= (s);                   \
} while(0)

/**
 * @brief adjusts given vector according to orientation vector such that axes are correct
 * @param measured pointer to measurment vector
 * @param orientation pointer to ortientation vector (in degrees)
 */
void coord_transform(Vector* measurement,  Vector* orientation);

void coord_transform_f(Vector* measurement,  Vector32* orientation);


#endif
