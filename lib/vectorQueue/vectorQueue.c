/**
 * @file vectorQueue.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include "vectorQueue.h"

uint8_t vq_enqueue(Vector* v, vectorQueue* q) {
  if(q->size < VECTOR_QUEUE_MAX_SIZE) {
    uint8_t s = (q->size)++;
    q->queue[s] = *v;
  }
}

uint8_t vq_free_space(vectorQueue* q) {
  return VECTOR_QUEUE_MAX_SIZE - q->size;
}

vectorQueue vq_copy(vectorQueue* q) {
  vectorQueue new;
  vectorQueue.queue = q->queue;
  memcpy(new.queue, q->queue, VECTOR_QUEUE_MAX_SIZE * sizeof(Vector));
}

vectorQueue vq_move(vectorQueue* q) {
  vectorQueue copy = vq_copy(q);
  q->size = 0;
  return copy;
}
