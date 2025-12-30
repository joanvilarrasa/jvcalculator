#include "cache.h"
#include <string.h>

void queue_init(Queue* q) {
  for (int i = 0; i < QUEUE_SIZE; i++) {
    q->lines[i][0] = '\0';
  }
  q->cut_index = 0;
}

void queue_enqueue(Queue* q, const char* line) {
    q->lines[q->cut_index] = line;
    q->cut_index = (q->cut_index + 1) % QUEUE_SIZE;
}

const char* queue_get(Queue* q, int x) {
  if (x < 0 || x >= QUEUE_SIZE) {
    return '\0';
  }
  return q->lines[(q->cut_index - 1 - x) % QUEUE_SIZE];
}