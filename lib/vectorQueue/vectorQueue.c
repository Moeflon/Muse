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

inline void vq_clear(vectorQueue* q) {
  q->size = 0;
}

Vector vq_average(vectorQueue* q) {
  Vector32 avg = { 0 };

  for(int i = 0; i < q->size; i++) {
    Vector val = q->queue[i];
    add_to_vector(&avg, &val);
  }

  div_vector(q->size, &avg);
  Vector avg16 = { avg.x, avg.y, avg.z };
  return avg16;
}
