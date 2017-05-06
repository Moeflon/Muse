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

#endif
