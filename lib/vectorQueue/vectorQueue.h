/**
 * @file vectorQueue.h
 * @brief FIFO data structure and operations
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef VECTOR_QUEUE_H_
#define VECTOR_QUEUE_H_

#include <vectorMaths.h>

/** Allocated size of queue */
#define VECTOR_QUEUE_MAX_SIZE 64
#define LG_VECTOR_QUEUE_MAX_SIZE 6

/** Amount of values to average together per new value in averaged queue */
#define QUEUE_AVERAGING_TRESHOLD 16
#define QUEUE_AVERAGING_BLOCK_SIZE 4

/**
 * @brief struct containing queue length and array
 */
typedef struct vectorQueue {
  Vector queue[VECTOR_QUEUE_MAX_SIZE]; /**> queue array */
  uint8_t size; /**> current queue size */
} vectorQueue;

/**
 * @brief Adds vector to end of queue and updates size, discards new value if max size is exceeded
 * @param v vectorpointer of vector to add
 * @param q pointer to vectorqueue to add to
 * @retval 0 successfully added
 * @retval 1 overflowed
 */
uint8_t vq_enqueue(Vector v, vectorQueue* q);

/**
 * @brief Returns how much free space there is left in the queue
 * @param q pointer to vectorqueue to read
 * @return free space
 */
uint8_t vq_free_space(vectorQueue* q);

/**
 * @brief sets size of vectorqueue to zero
 * @param q vectorqueue to clear
 */
void vq_clear(vectorQueue* q);

/**
 * @brief Averages queue
 * @param queue to average
 * @return average vector
 */
Vector vq_average(vectorQueue* q);

/**
 * @brief Calculates the sum of deviations from average
 * @param queue to deviate
 * @param center vector around which to calulate deviation
 * @return deviation
 */
Vector vq_deviation(vectorQueue* q, Vector* center);

/**
  * @brief Smooths a queue using a moving average
  */
void vq_smooth(vectorQueue* q);
#endif
