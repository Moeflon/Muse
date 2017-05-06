/**
 * @file vectorMaths.h
 * @brief Quaternion operation definitions
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef QUATERNION_MATHS_H_
#define QUATERNION_MATHS_H_

#include <stdint.h>
#include <vectorMaths.h>

/**
 * @brief A quaternion
 */
typedef struct Quaternion {
  float w; /**> z component */
  float x; /**> x component */
  float y; /**> y component */
  float z; /**> z component */
} Quaternion32;

#define clear_quat(a) do {              \
  (a)->w = 0;                           \
  (a)->x = 0;                           \
  (a)->y = 0;                           \
  (a)->z = 0;                           \
} while(0)

#define add_quats(a, b, c) do {         \
  (c)->w = (a)->w + (b)->w;             \
  (c)->x = (a)->x + (b)->x;             \
  (c)->y = (a)->y + (b)->y;             \
  (c)->z = (a)->z + (b)->z;             \
} while(0)

#define sub_quats(a, b, c) do {         \
  (c)->w = (a)->w - (b)->w;             \
  (c)->x = (a)->x - (b)->x;             \
  (c)->y = (a)->y - (b)->y;             \
  (c)->z = (a)->z - (b)->z;             \
} while(0)

#define add_to_quat(a, b) do {          \
  (a)->w += (b)->w;                     \
  (a)->x += (b)->x;                     \
  (a)->y += (b)->y;                     \
  (a)->z += (b)->z;                     \
} while(0)

#define sub_from_quat(a, b) do {        \
  (a)->w -= (b)->w;                     \
  (a)->x -= (b)->x;                     \
  (a)->y -= (b)->y;                     \
  (a)->z -= (b)->z;                     \
} while(0)

#define div_scal_quats(s, a, b) do {    \
  (b)->w = (a)->w / (s);                \
  (b)->x = (a)->x / (s);                \
  (b)->y = (a)->y / (s);                \
  (b)->z = (a)->z / (s);                \
} while(0)

#define mul_scal_quats(s, a, b) do {    \
  (b)->w = (a)->w * (s);                \
  (b)->x = (a)->x * (s);                \
  (b)->y = (a)->y * (s);                \
  (b)->z = (a)->z * (s);                \
} while(0)

#define div_scal_quat(s, a) do {        \
  (a)->w /= (s);                        \
  (a)->x /= (s);                        \
  (a)->y /= (s);                        \
  (a)->z /= (s);                        \
} while(0)

#define mul_scal_quat(s, a) do {        \
  (a)->w *= (s);                        \
  (a)->x *= (s);                        \
  (a)->y *= (s);                        \
  (a)->z *= (s);                        \
} while(0)
#endif

#define mul_quats(a, b, c) do {                                                                           \
  (c)->w = ((a)->w * (b)->w) - ((a)->x * (b)->x) - ((a)->y * (b)->y) - ((a)->z * (b)->z);                 \
  (c)->x = ((a)->w * (b)->x) + ((a)->x * (b)->w) + ((a)->y * (b)->z) - ((a)->z * (b)->y);                 \
  (c)->y = ((a)->w * (b)->y) - ((a)->x * (b)->z) + ((a)->y * (b)->w) + ((a)->z * (b)->x);                 \
  (c)->z = ((a)->w * (b)->z) - ((a)->x * (b)->y) + ((a)->y * (b)->x) + ((a)->z * (b)->w);                 \
} while(0)

#define mul_quat(a, b) do {                                                                               \
  (a)->w = ((a)->w * (b)->w) - ((a)->x * (b)->x) - ((a)->y * (b)->y) - ((a)->z * (b)->z);                 \
  (a)->x = ((a)->w * (b)->x) + ((a)->x * (b)->w) + ((a)->y * (b)->z) - ((a)->z * (b)->y);                 \
  (a)->y = ((a)->w * (b)->y) - ((a)->x * (b)->z) + ((a)->y * (b)->w) + ((a)->z * (b)->x);                 \
  (a)->z = ((a)->w * (b)->z) - ((a)->x * (b)->y) + ((a)->y * (b)->x) + ((a)->z * (b)->w);                 \
} while(0)

/**
 * @brief Normalizes given quaternion
 * @param q quaternion
 */
float quat_norm(Quaternion32* q);

/**
 * @brief Normalizes given quaternion
 * @param q quaternion
 */
void normalize_quat(Quaternion32* q);

/**
 * @brief Converts quaternion to euler angles
 * @param q quaternion
 * @return Floating point vector containing euler angles
 */
Vectorf quat_to_euler(Quaternion* q);
