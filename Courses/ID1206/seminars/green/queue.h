#ifndef _QUEUE
#define _QUEUE

typedef struct Queue {
  struct green_t *front;
  struct green_t *rear;
  int length;
} Queue;

struct Queue *create_queue(void);

/* Update formal param *thread from green_t to void to make
   more general */
void enqueue(struct Queue *queue, void *thread);
struct green_t *dequeue(struct Queue *queue);

#endif

