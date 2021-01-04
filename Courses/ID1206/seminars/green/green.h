#ifndef _GREEN
#define _GREEN

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

typedef struct green_cond_t {
  struct green_t *susp_list;
} green_cond_t;

typedef struct green_mutex_t {
  volatile int taken;
  struct green_t *susp;
} green_mutex_t;

typedef struct queue {
  green_t rear;
  green_t front;
  int length;
} queue;


/* Green functions */
int green_create(struct green_t *thread, void *(*fun)(void *), void *arg);
int green_yield();
int green_join(struct green_t *thread, void** res);

/* Cond functions */
void green_cond_init(green_cond_t *cond);
void green_cond_wait(green_cond_t *cond);
void green_cond_signal(green_cond_t *cond);

/* mutex functions */
int green_mutex_init(green_mutex_t *mutex);
int green_mutex_lock(green_mutex_t *mutex);
int green_mutex_unlock(green_mutex_t *mutex);

/* other functions */
green_t *dequeue(green_t **list);
void enqueue(green_t **list, green_t *thread);
void green_thread(void);
void timer_handler(int);

#endif
