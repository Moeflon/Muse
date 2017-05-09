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
 * @brief sine lookup table
 */
extern const uint8_t sin_table[91];

/** @brief extra large sine lookup table
 *
 */
extern const int32_t sin_table_xl[1001];

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
 * @brief Returns sin from lookuptable, fixed point multiplied by 1000000
 * @param degrees
 * @return sine multiplied by 1000000
 */
int32_t sin_xl(int32_t angle);

/**
 * @brief Returns cos from lookuptable, fixed point multiplied by 1000000
 * @param degrees
 * @return cosine multiplied by 1000000
 */
int32_t cos_xl(int32_t angle);

#endif
