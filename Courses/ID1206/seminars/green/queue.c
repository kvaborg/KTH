#include "green.h"
#include "queue.h"
#include <stdlib.h>

struct Queue *create_queue() {

  struct Queue *queue = (struct Queue*)malloc(sizeof(struct Queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

/*
    Enqueue is performed by a producing thread. An element
    is inserted at the rear end of the queue. The next pointer 
    of the thread points to the element that is 
    closer to the rear end of the queue realtive to itself. 
*/
void enqueue(struct Queue *queue, void *thread) {

  /* If queue is empty */
  if (queue->rear == NULL) {
    queue->front = queue->rear = thread;
    queue->length += 1;
    return;
  } 

  /* If queue is NOT empty */
  queue->rear->next = thread;
  queue->rear = thread;
  queue->length += 1;
}

struct green_t *dequeue(struct Queue *queue) {

  /* If the queue is empty, return NULL */
  if (queue->front == NULL) {
    queue->rear = NULL;
    return NULL;
  }

  green_t *temp = queue->front;

  queue->front = queue->front->next;

  queue->length -= 1;
  return temp;
  
}
