/**
 * @file vectorQueue.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include "vectorQueue.h"

uint8_t vq_enqueue(Vector v, vectorQueue* q) {
  if(q->size < VECTOR_QUEUE_MAX_SIZE) {
    uint8_t s = q->size;
    q->queue[s] = v;
    (q->size)++;
    return 0;
  }
  return 1;
}

inline uint8_t vq_free_space(vectorQueue* q) {
  return VECTOR_QUEUE_MAX_SIZE - q->size;
}

inline void vq_swap(vectorQueue** a, vectorQueue** b) {
  vectorQueue* c = *a;
  *a = *b;
  *b = c;
}

inline void vq_clear(vectorQueue* q) {
  q->size = 0;
}

uint8_t vq_average(vectorQueue* q) {
  if(q->size < QUEUE_AVERAGING_TRESHOLD) return 1;

  uint8_t block_index = 0; /* Current index of averaged queue */
  uint8_t averaged = 0; /* Amount of values already averaged to block */
  uint8_t sample_size = q->size; /* Amount of samples in buffer */

  for(int i = 0; i < sample_size; i++) {
    if(averaged < QUEUE_AVERAGING_BLOCK_SIZE) {
      /* Divide current value by averaging amount */
      div_vector(QUEUE_AVERAGING_BLOCK_SIZE, &q->queue[i]);

      /* Add current value to current averaged queue index */
      if(i != 0) { /* if i == 0 the value we'd add is already in place */
        add_to_vector(&q->queue[block_index], &q->queue[i]);
      }

      /* Amound of samples remaining */
      q->last_block_size = vq_free_space(q);

      /* Subtract queue size for free_space function */
      q->size -= (q->last_block_size >= QUEUE_AVERAGING_BLOCK_SIZE) ? QUEUE_AVERAGING_BLOCK_SIZE : q->last_block_size;
      averaged++;
    }
    else {
      block_index++;

      /* Clear vector to accomodate new averaged values */
      clear_vector(&q->queue[block_index]);

      /* New block, new start */
      averaged = 0;
    }
  }

  /* Set size of final averaged queue */
  q->size = block_index + 1;

  return 0;
}
