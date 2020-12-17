#ifndef _QUEUE
#define _QUEUE

#include "green.h"

struct Queue {
  struct green_t *front;
  struct green_t *rear;
  int length;
};

struct Queue *create_queue(void);
void enqueue(struct Queue *queue, struct green_t *thread);
void dequeue(struct Queue *queue);

#endif

