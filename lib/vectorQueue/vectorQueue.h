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

/** Amount of values to average together per new value in averaged queue */
#define QUEUE_AVERAGING_TRESHOLD 16
#define QUEUE_AVERAGING_BLOCK_SIZE 4

/**
 * @brief struct containing queue length and array
 */
typedef struct vectorQueue {
  Vector queue[VECTOR_QUEUE_MAX_SIZE]; /**> queue array */
  uint8_t size; /**> current queue size */
  uint8_t last_block_size; /**> size mod QUEUE_AVERAGING_BLOCK_SIZE (after averaging) */
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
 * @brief swaps memory locations of vectorqueues
 * @param a operand
 * @param b operand
 */
void vq_swap(vectorQueue** a, vectorQueue** b);

/**
 * @brief sets size of vectorqueue to zero
 * @param q vectorqueue to clear
 */
void vq_clear(vectorQueue* q);

/**
 * @brief Averages queue into new smaller queue. Averages QUEUE_AVERAGING_BLOCK_SIZE
 *        values per new value. Also sets the last_block_size field in the struct.
 *        Only averages if amount of values in queue exceeds QUEUE_AVERAGING_TRESHOLD
 * @param q vectorqueue to average
 * @retval 0 averaged
 * @retval 1 didn't average
 */
uint8_t vq_average(vectorQueue* q);
#endif
