/**
 * @file vectorMaths.h
 * @brief Quaternion operation definitions
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef QUATERNION_MATHS_H_
#define QUATERNION_MATHS_H_

#include <stdint.h>

/**
 * @brief A quaternion
 */
typedef struct Quaternion {
  int32_t w; /**> z component */
  int32_t x; /**> x component */
  int32_t y; /**> y component */
  int32_t z; /**> z component */
} Quaternion;

#endif
