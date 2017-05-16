/**
 * @file lookupMaths.h
 * @brief Trigonomic functions for use in coordinate transformations
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef LOOKUP_MATHS_H_
#define LOOKUP_MATHS_H_

#include <stdint.h>

#define TRIG_SHIFT 15

/**
 * @brief Returns cos from lookup table, TRIG_SHIFT_AMOUNT times shifted to left
 * @param angle angle in degrees*10
 * @return sine multiplied by TRIG_SHIFT_AMOUNT shifted to left
 */
int16_t lu_sin(int16_t angle);

/**
 * @brief Returns cos from lookup table, TRIG_SHIFT_AMOUNT times shifted to left
 * @param angle angle in degrees*10
 * @return cosine TRIG_SHIFT_AMOUNT times shifted to left
 */
int16_t lu_cos(int16_t angle);

/**
 * @brief Calculates integer sqrt of 16-bit unsigned number using binary search in a lookup table
 * @param x number to sqrt
 * @see http://stackoverflow.com/a/5296669
 */
uint8_t lu_sqrt(uint16_t x);

/**
 * @brief Calculates integer sqrt of 32-bit unsigned number using binary search in a lookup table
 * @param x number to sqrt
 */
uint16_t lu_sqrt32(uint32_t x);

/**
 * @brief Lookup version of the well known atan2() functions
 * @param numerator numerator of value to get arctan of
 * @param denominator denominator of value to get arctan of
 * @return a value between -1800 and + 1800, 10 ~ 1 degree
 */
int16_t lu_arctan(int16_t numerator, int16_t denominator);

#endif
