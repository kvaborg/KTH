#include <stdlib.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include <assert.h>
#include "green.h"
#include "queue.h"

#define FALSE 0
#define TRUE 1

#define STACK_SIZE 4096

static ucontext_t main_ctnx = {0};
static struct green_t main_green = {&main_ctnx, NULL, NULL, NULL, NULL, NULL, FALSE};

static green_t *running = &main_green;

static void init() __attribute__((constructor));

struct Queue *ready_queue = NULL;

/* Get main context and initialize ready_queue when program is loaded */
void init() {
  getcontext(&main_ctnx);
  ready_queue = create_queue();
}

void green_thread() {
  green_t *this = running;

  void *result = (*this->fun)(this->arg);

  /* TODO: Place waiting (joining) thread in ready queue) */
  if (this->join != NULL) {
    enqueue(ready_queue, this->join);
  }

  /* TODO: save result of execution */
  this->retval = result;

  /* TODO: We're a zombie */
  this->zombie = TRUE;

  /* TODO: find the next thread to run */
  green_t *next = ready_queue->front;
  running = next;
  dequeue(ready_queue);
  setcontext(next->context);
}

int green_create(green_t *new, void *(*fun)(void*), void *arg) {

  ucontext_t *cntx = (ucontext_t *)malloc(sizeof(ucontext_t));
  getcontext(cntx);

  void *stack = malloc(STACK_SIZE);

  cntx->uc_stack.ss_sp = stack;
  cntx->uc_stack.ss_size = STACK_SIZE;
  makecontext(cntx, green_thread, 0);

  new->context = cntx;
  new->fun = fun;
  new->arg = arg;
  new->next = NULL;
  new->join = NULL;
  new->retval = NULL;
  new->zombie = FALSE;

  /* TODO: Add to the ready queue */
  enqueue(ready_queue, new);
  return 0;
}

int green_yield() {
  green_t *susp = running;

  // Add susp to ready queue
  enqueue(ready_queue, susp);
  
  // Select the next thread for execution
  green_t *next = ready_queue->front;
  running = next;
  dequeue(ready_queue);
  swapcontext(susp->context, next->context);

  return 0;
}

int green_join(struct green_t *thread, void **res) {
  if (!thread->zombie) {
    green_t *susp = running;

    // Add as joining thread
    thread->join = susp;
    
    //select the next thread for execution
    green_t *next = ready_queue->front;
    running = next;
    dequeue(ready_queue);
    swapcontext(susp->context, next->context);
  } 
  // collect result
  thread->retval = res;

  // free context
  free(thread->context);

  return 0;
}
