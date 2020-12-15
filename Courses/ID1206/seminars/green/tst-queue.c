#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "green.h"

void *funA(void *arg) {
  printf("A\n");
  return NULL;
}

void *funB(void *arg) {
  printf("B\n");
  return NULL;
}

void *funC(void *arg) {
  printf("C\n");
  return NULL;
}

void sanity(struct Queue *queue) {
  green_t *temp = (struct green_t*)queue->front;
  while(temp != NULL) {
    (*temp->fun)(NULL);
    temp = temp->next;
  }
  if (queue->length == 0) {
    printf("-- List is empty --\n");
    printf("Length: %d\n\n", queue->length);
  } else {
    printf("Length: %d\n\n", queue->length);
  }
}

int main() {
//  struct Queue *queue = create_queue();

  green_t *a = (green_t*)malloc(sizeof(green_t));
  green_t *b = (green_t*)malloc(sizeof(green_t));
  green_t *c = (green_t*)malloc(sizeof(green_t));

  green_create(a, funA, NULL);
  green_create(b, funB, NULL);
  green_create(c, funC, NULL);

//  a->fun = funA;
//  b->fun = funB;
//  c->fun = funC;

//  enqueue(queue, a);
//  enqueue(queue, b);
//  enqueue(queue, c);
  sanity(ready_queue);

  dequeue(ready_queue);
  dequeue(ready_queue);
  dequeue(ready_queue);
  dequeue(ready_queue);
  sanity(ready_queue);

  return 0;
}
