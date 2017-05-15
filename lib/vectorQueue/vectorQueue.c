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

  if(vq_free_space(q) > 0) {
    div_vector(q->size, &avg);
  }
  else {
    shr_vector(LG_VECTOR_QUEUE_MAX_SIZE, &avg);
  }

  Vector avg16 = { avg.x, avg.y, avg.z };
  return avg16;
}

Vector vq_deviation(vectorQueue* q, Vector* center) {
  Vector deviation = { 0 };

  for(int i = 0; i < q->size; i++) {
    Vector d;
    sub_vectors(center, &q->queue[i], &d);
    abs_vector(&d);
    add_to_vector(&deviation, &d);
  }

  return deviation;
}

void vq_smooth(vectorQueue* q){
  if(q->size > 3){
    const int end = q->size - 1;
    const Vector* q_q = q->queue;
    for(int i = 1; i < end; i++){
      q->queue[i].x = ((int32_t)(q_q[i-1].x) + q_q[i].x + q_q[i+1].x)/3;
      q->queue[i].y = ((int32_t)(q_q[i-1].y) + q_q[i].y + q_q[i+1].y)/3;
      q->queue[i].z = ((int32_t)(q_q[i-1].z) + q_q[i].z + q_q[i+1].z)/3;
    }
  }
}
