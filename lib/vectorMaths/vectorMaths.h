/*
 * vectorMaths.h
 */

#ifndef VECTOR_MATHS_H_
#define VECTOR_MATHS_H_

#include <stdint.h>

typedef struct Vector {
  int16_t x;
  int16_t y;
  int16_t z;
} Vector;

/**
 * @brief adds operand Vectors and stores it in supplied pointer
 * @param operand 1
 * @param operand 2
 * @param destination pointer
 */
void add_vector(Vector*, Vector*, Vector*);

/**
 * @brief subtracts operand Vectors left to right and stores it in supplied pointer
 * @param operand 1
 * @param operand 2
 * @param destination pointer
 */
void sub_vector(Vector*, Vector*, Vector*);

/**
 * @brief devides vector by a given power of 2
 * @param power of two
 * @param pointer to vector we want to devide
 * @param pointer to destionation vector
 */
void div_pow_two_vector(int, Vector*, Vector*);

/**
 * @brief calculates normal
 * @return norm
 */
uint16_t vector_norm(Vector*);

#endif
