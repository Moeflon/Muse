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
uint8_t vq_enqueue(Vector* v, vectorQueue* q);

/**
 * @brief Returns how much free space there is left in the queue
 * @param q pointer to vectorqueue to read
 * @return free space
 */
uint8_t vq_free_space(vectorQueue* q);

/**
 * @brief Returns copy of given queue
 * @param q pointer to vectorqueue to copy
 * @return new vectorQueue
 */
vectorQueue vq_copy(vectorQueue* q);

/**
 * @brief Returns copy of given queue and resets it
 * @param q pointer to vectorqueue to move
 * @return vectorqueue
 */
vectorQueue vq_move(vectorQueue* q);

#endif
