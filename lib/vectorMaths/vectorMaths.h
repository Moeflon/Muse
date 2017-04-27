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
 * @brief sine lookup table
 */
extern const uint8_t sin_table[91];

/**
 * @brief converts vector to 32-bit vector
 * @param v vector
 * @return 32-bit vector
 */
Vector32 vector_to_vector32(Vector* v);

/**
 * @brief converts 32-bit vector to 16-bit vector
 * @param v vector
 * @return 16-bit vector
 */
Vector vector32_to_vector(Vector* v32);

/**
 * @brief adds operand Vectors and stores it in supplied pointer
 * @param a operand 1
 * @param b operand 2
 * @param [out] dest destination pointer
 */
void add_vector(Vector* a, Vector* b, Vector* dest);

/**
 * @brief adds operand Vectors and stores it in supplied pointer
 * @param a operand 1
 * @param b operand 2
 * @param [out] dest destination pointer
 */
void add_vector32(Vector32* a, Vector32* b, Vector32* dest);

/**
 * @brief subtracts operand Vectors left to right and stores it in supplied pointer
 * @param a operand 1
 * @param b operand 2
 * @param [out] dest destination pointer
 */
void sub_vector(Vector* a, Vector* b, Vector* dest);

/**
 * @brief subtracts operand Vectors left to right and stores it in supplied pointer
 * @param a operand 1
 * @param b operand 2
 * @param [out] dest destination pointer
 */
void sub_vector32(Vector32* a, Vector32* b, Vector32* dest);

/**
 * @brief devides vector by a given power of 2
 * @param pow power of two
 * @param a pointer to vector we want to devide
 * @param [out] dest pointer to destionation vector
 */
void div_pow_two_vector(uint8_t pow, Vector* a, Vector* dest);

/**
 * @brief devides vector by a given scalar
 * @param scal scalar
 * @param a pointer to vector we want to devide
 * @param [out] dest pointer to destionation vector
 */
void div_scal_vector(int16_t scal, Vector* a, Vector* dest);

/**
 * @brief devides vector by a given scalar
 * @param scal scalar
 * @param a pointer to vector we want to devide
 * @param [out] dest pointer to destionation vector
 */
void div_scal_vector32(int16_t scal, Vector32* a, Vector32* dest);

/**
 * @brief multiplies vector by a given scalar
 * @param scal scalar
 * @param a pointer to vector we want to multiply
 * @param [out] dest pointer to destionation vector
 */
void mul_scal_vector32(int16_t scal, Vector32* a, Vector32* dest);

/**
 * @brief multiplies vector by a given power of 2
 * @param pow power of two
 * @param a pointer to vector we want to devide
 * @param [out] dest pointer to destionation vector
 */
void mul_pow_two_vector(uint8_t pow, Vector* a, Vector* dest);

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

/**
 * @brief calculates normal
 * @return norm
 */
uint16_t vector_norm(Vector* a);

#endif
