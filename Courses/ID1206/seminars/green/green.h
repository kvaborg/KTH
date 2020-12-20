#ifndef _GREEN
#define _GREEN

#include "queue.h"
#include <sys/ucontext.h>
#include <ucontext.h>

typedef struct green_t {
  ucontext_t *context;
  void *(*fun)(void *);
  void *arg;
  struct green_t *next;
  struct green_t *join;
  void *retval;
  int zombie;
} green_t;

extern struct Queue *ready_queue;

int green_create(struct green_t *thread, void *(*fun)(void *), void *arg);
int green_yield();
int green_join(struct green_t *thread, void** res);
void green_thread(void);
void green_cond_init(green_cond_t *cond);
void green_cond_wait(green_cond_t *cond);
void green_cond_signal(green_cond_t *cond);

#endif
