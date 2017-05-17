/**
 * @file vectorQueue.h
 * @brief FIFO data structure and operations
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#ifndef VECTOR_QUEUE_H_
#define VECTOR_QUEUE_H_

#include "../vectorMaths/vectorMaths.h"

#define VECTOR_QUEUE_MAX_SIZE 64 /**> Allocated size of queue */
#define LG_VECTOR_QUEUE_MAX_SIZE 6 /**> Lg of allocated size of queue */

/**
 * @brief struct containing queue length and array
 */
typedef struct vectorQueue {
  Vector queue[VECTOR_QUEUE_MAX_SIZE]; /**> queue array */
  uint8_t size; /**> current queue size */
} vectorQueue;

/**
 * @brief Adds vector to end of queue and updates size, discards new value if max size is exceeded
 * @param v vector pointer of vector to add
 * @param q pointer to vectorQueue to add to
 * @retval 0 successfully added
 * @retval 1 overflowed
 */
uint8_t vq_enqueue(Vector v, vectorQueue* q);

/**
 * @brief Returns how much free space there is left in the queue
 * @param q pointer to vectorQueue to read
 * @return free space
 */
uint8_t vq_free_space(vectorQueue* q);

/**
 * @brief Sets size of vectorQueue to zero
 * @param q pointer to vectorQueue to clear
 */
void vq_clear(vectorQueue* q);

/**
 * @brief Averages queue
 * @param q pointer to vectorQueue to average
 * @return average vector
 */
Vector vq_average(vectorQueue* q);

/**
 * @brief Calculates the sum of deviations from average
 * @param q pointer to vectorQueue to deviate
 * @param center vector around which to calulate deviation
 * @return absolute sum of deviations
 */
Vector vq_deviation(vectorQueue* q, Vector* center);

/**
 * @brief Smooths a queue using a moving average
 * @param q pointer to vectorQueue to smoothe
 */
void vq_smooth(vectorQueue* q);

/**
 * @brief Removes peaks from queue and replaces them with given value
 * @param q queue to remove peaks from
 * @param average the average vector around which peaks are detected and peaks are replaced with
 * @param treshold treshold value around given average value
 */
void vq_remove_peaks(vectorQueue* q, Vector* average, int16_t treshold);
#endif
