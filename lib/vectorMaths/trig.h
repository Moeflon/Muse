/**
 * @file trig.h
 * @brief Trigonomic functions for use in coordinate transformations
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef VECTOR_TRIG_H_
#define VECTOR_TRIG_H_

#include <stdint.h>

/**
 * @brief sine table with 901 values, 900 ~ 90 degrees, sin_lookup(900) = 32767
 */
extern const int16_t sin_table[901];

/**
 * @brief Returns sin from lookup table, fixed point multiplied by 32767
 * @param angle in degrees*10
 * @return sine multiplied by 32767
 */
int16_t sin_shift(int16_t angle);

/**
 * @brief Returns sin from lookup table, fixed point multiplied by 32767
 * @param angle in degrees*10
 * @return cosine multiplied by 32767
 */
int16_t cos_shift(int16_t angle);

#endif
