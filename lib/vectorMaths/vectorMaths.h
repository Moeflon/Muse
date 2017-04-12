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
 * @brief adds operand Vectors and stores it in supplied pointer
 * @param a operand 1
 * @param b operand 2
 * @param [out] dest destination pointer
 */
void add_vector(Vector* a, Vector* b, Vector* dest);

/**
 * @brief subtracts operand Vectors left to right and stores it in supplied pointer
 * @param a operand 1
 * @param b operand 2
 * @param [out] dest destination pointer
 */
void sub_vector(Vector* a, Vector* b, Vector* dest);

/**
 * @brief devides vector by a given power of 2
 * @param pow power of two
 * @param a pointer to vector we want to devide
 * @param [out] dest pointer to destionation vector
 */
void div_pow_two_vector(uint8_t pow, Vector* a, Vector* dest);

/**
 * @brief multiplies vector by a given power of 2
 * @param pow power of two
 * @param a pointer to vector we want to devide
 * @param [out] dest pointer to destionation vector
 */
void mul_pow_two_vector(uint8_t pow, Vector* a, Vector* dest);

/**
 * @brief calculates normal
 * @return norm
 */
uint16_t vector_norm(Vector* a);

#endif
