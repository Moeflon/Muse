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

#define add_vectors(a, b, c) do {   \
  (c)->x = (a)->x + (b)->x;         \
  (c)->y = (a)->y + (b)->y;         \
  (c)->z = (a)->z + (b)->z;         \
} while 0

#define sub_vectors(a, b, c) do {   \
  (c)->x = (a)->x - (b)->x;         \
  (c)->y = (a)->y - (b)->y;         \
  (c)->z = (a)->z - (b)->z;         \
} while 0

#define add_to_vector(a, b) do {   \
  (a)->x += (b)->x;                \
  (a)->y += (b)->y;                \
  (a)->z += (b)->z;                \
} while 0

#define sub_from_vector(a, b) do { \
  (a)->x -= (b)->x;                \
  (a)->y -= (b)->y;                \
  (a)->z -= (b)->z;                \
} while 0

#define div_vectors(s, a, b) do {  \
  (b)->x = (a)->x / (s);           \
  (b)->y = (a)->y / (s);           \
  (b)->z = (a)->z / (s);           \
} while 0

#define mul_vectors(s, a, b) do {  \
  (b)->x = (a)->x * (s);           \
  (b)->y = (a)->y * (s);           \
  (b)->z = (a)->z * (s);           \
} while 0

#define div_vector(s, a) do {      \
  (a)->x /= (s);                   \
  (a)->y /= (s);                   \
  (a)->z /= (s);                   \
} while 0

#define mul_vector(s, a) do {      \
  (a)->x *= (s);                   \
  (a)->y *= (s);                   \
  (a)->z *= (s);                   \
} while 0

/**
 * @brief sine lookup table
 */
extern const uint8_t sin_table[91];

/**
 * @brief Returns sin from lookuptable, fixed point multiplied by 100
 * @param degrees
 * @return sine multiplied by 100
 */
int8_t sin100(int16_t degrees);

/**
 * @brief Returns cos from lookuptable, fixed point multiplied by 100
 * @param degrees
 * @return cosine multiplied by 100
 */
int8_t cos100(int16_t degrees);

/**
 * @brief adjusts given vector according to orientation vector such that axes are correct
 * @param measured pointer to measurment vector
 * @param m_scale number of measurement units are one physical unit (be careful for overflow)
 * @param orientation pointer to ortientation vector
 * @param o_scale number of orientation units are one physical unit (be careful for overflow)
 */
void coord_transform(Vector* measurement, int16_t m_scale,  Vector* orientation, int16_t o_scale);

#endif
