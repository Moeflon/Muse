/**
 * @file lookupMaths.h
 * @brief Trigonomic functions for use in coordinate transformations
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef LOOKUP_MATHS_H_
#define LOOKUP_MATHS_H_

#include <stdint.h>

#define TRIG_SHIFT_AMOUNT 15

/**
 * @brief sine table with 901 values, 900 ~ 90 degrees, sin_lookup(900) = 32767
 */
extern const int16_t sin_table[901];

/**
 * @brief table containing all 16-bit squares
 */
extern const uint16_t squares_table[256];

/**
 * @brief Returns sin from lookup table, fixed point TRIG_SHIFT_AMOUNT times shifted to left
 * @param angle in degrees*10
 * @return sine multiplied by TRIG_SHIFT_AMOUNT shifted to left
 */
int16_t lu_sin(int16_t angle);

/**
 * @brief Returns sin from lookup table, TRIG_SHIFT_AMOUNT times shifted to left
 * @param angle in degrees*10
 * @return cosine TRIG_SHIFT_AMOUNT times shifted to left
 */
int16_t lu_cos(int16_t angle);

/**
 * @brief Calculates integer sqrt of 16-bit unsigned number using binary search in a lookup table
 * @param x number to sqrt
 * @see http://stackoverflow.com/a/5296669
 */
uint8_t lu_sqrt(uint16_t x);

#endif
