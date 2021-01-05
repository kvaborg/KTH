#define _POSIX_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include <assert.h>
#include "green.h"

#define FALSE 0
#define TRUE 1

#define STACK_SIZE 4096
#define PERIOD 100

/* private functions */

static ucontext_t main_ctnx = {0};
static struct green_t main_green = {&main_ctnx, NULL, NULL, NULL, NULL, NULL, FALSE};

static green_t *running = &main_green;
static sigset_t block;

struct green_t *ready_queue = NULL;

static void init() __attribute__((constructor));

/* Get main context and initialize ready_queue when program is loaded */
void init() {
  getcontext(&main_ctnx);

  sigemptyset(&block);
  sigaddset(&block, SIGVTALRM);

  struct sigaction act = {0};
  struct timeval interval;
  struct itimerval period;

  act.sa_handler = timer_handler;
  assert(sigaction(SIGVTALRM, &act, NULL) == 0);

  interval.tv_sec = 0;
  interval.tv_usec = PERIOD;
  period.it_interval = interval;
  period.it_value = interval;
  setitimer(ITIMER_VIRTUAL, &period, NULL);
}

void timer_handler(int sig) {

  char *buf = "INTERRUPT!\n\n";
  write(1, buf, sizeof(buf));

  green_yield();
}

void green_thread() {
  sigprocmask(SIG_BLOCK, &block, NULL);
  green_t *this = running;

  void *result = (*this->fun)(this->arg);

  /* Place waiting (joining) thread in ready queue) */
  if (this->join != NULL) {
    enqueue(&ready_queue, this->join);
  }

  /* save result of execution */
  this->retval = result;

  /* We're a zombie */
  this->zombie = TRUE;

  /* find the next thread to run */
  green_t *next = dequeue(&ready_queue);
  running = next;
  setcontext(next->context);
  sigprocmask(SIG_UNBLOCK, &block, NULL);
}

int green_create(green_t *new, void *(*fun)(void*), void *arg) {
  sigprocmask(SIG_BLOCK, &block, NULL);

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

  /* Add to the ready queue */
  enqueue(&ready_queue, new);
  sigprocmask(SIG_UNBLOCK, &block, NULL);
  return 0;
}

int green_yield() {
  sigprocmask(SIG_BLOCK, &block, NULL);

  green_t *susp = running;

  // Add susp to ready queue
  enqueue(&ready_queue, susp);
  
  // Select the next thread for execution
  green_t *next = dequeue(&ready_queue);
  running = next;
  swapcontext(susp->context, next->context);
  sigprocmask(SIG_UNBLOCK, &block, NULL);

  return 0;
}

int green_join(struct green_t *thread, void **res) {

  if (thread->zombie)
    return 0;

  sigprocmask(SIG_BLOCK, &block, NULL);

  green_t *susp = running;

  // Add as joining thread
  thread->join = susp;
  
  //select the next thread for execution
  green_t *next = dequeue(&ready_queue);
  running = next;
  swapcontext(susp->context, next->context);

  // collect result
  if (thread->retval != NULL) {
    *res = thread->retval;
  }

  // free context
  free(thread->context);

  sigprocmask(SIG_UNBLOCK, &block, NULL);

  return 0;
}

/* Initialize a green condition variable.
   Cond points to the queue of suspended threads */
void green_cond_init(green_cond_t *cond) {
  sigprocmask(SIG_BLOCK, &block, NULL);

  cond->susp_list = NULL;

  sigprocmask(SIG_UNBLOCK, &block, NULL);
}

/* Suspend the current thread on the condition.
   Cond points to the queue of suspended threads */
void green_cond_wait(green_cond_t *cond, green_mutex_t *mutex) {
  // block timer interrupt
  sigprocmask(SIG_BLOCK, &block, NULL);

  // suspend the running thread on condition
  green_t *susp = running;
  enqueue(&cond->susp_list, susp);

  if (mutex != NULL) {
    // release the lock if we have a mutex
    mutex->taken = FALSE;

    // move suspended thread to ready queue
    green_t *ready = dequeue(&mutex->susp);
    enqueue(&ready_queue, ready);
    mutex->susp = NULL;
  }

  // schedule next thread
  green_t *next = dequeue(&ready_queue);
  running = next;
  swapcontext(susp->context, next->context);

  if (mutex != NULL) {
    // try to take the lock
    if (mutex->taken) {
      // bad luck, suspend
      green_t *susp = running;
      enqueue(&mutex->susp, susp);

      green_t *next = dequeue(&ready_queue);
      running = next;
      swapcontext(susp->context, next->context);
    } else {
      // take the lock
      green_mutex_lock(mutex);
    }
  }

  //unblock
  sigprocmask(SIG_UNBLOCK, &block, NULL);
}

/* Move the first suspended thread to the ready queue.
   Cond points to the queue of suspended threads */
void green_cond_signal(green_cond_t *cond) {
  sigprocmask(SIG_BLOCK, &block, NULL);

  if (cond->susp_list == NULL) {
    return;
  }

  green_t *ready = dequeue(&cond->susp_list);
  enqueue(&ready_queue, ready);

  sigprocmask(SIG_UNBLOCK, &block, NULL);
}

int green_mutex_init(green_mutex_t *mutex) {
  sigprocmask(SIG_BLOCK, &block, NULL);

  //Initialize fields
  mutex->susp = NULL;
  mutex->taken = FALSE;

  sigprocmask(SIG_UNBLOCK, &block, NULL);

  return 0;
}

int green_mutex_lock(green_mutex_t *mutex) {
  sigprocmask(SIG_BLOCK, &block, NULL);

  green_t *susp = running;

  if (mutex->taken) {
    // suspend the current thread
    enqueue(&mutex->susp, susp);

    // find the next thread
    green_t *next = dequeue(&ready_queue);
    running = next;
    swapcontext(susp->context, next->context);
  } else {
    // take the lock
    mutex->taken = TRUE;
  }
  // unblock
  sigprocmask(SIG_UNBLOCK, &block, NULL);

  return 0;
}

int green_mutex_unlock(green_mutex_t *mutex) {
  sigprocmask(SIG_BLOCK, &block, NULL);

  if (mutex->susp != NULL) {
    green_t *ready = dequeue(&mutex->susp);
    enqueue(&ready_queue, ready);
  } else {
    mutex->taken = FALSE;
    mutex->susp = NULL;
  }

  sigprocmask(SIG_UNBLOCK, &block, NULL);

  return 0;
}

green_t *dequeue(green_t **list) {
  if (*list == NULL) {
    return NULL;
  } else {
    green_t *thread = *list;
    *list =(*list)->next;
    thread->next = NULL;
    return thread;
  } 
}

void enqueue(green_t **list, green_t *thread) {
  if (*list == NULL) {
    *list = thread;
  } else {
    green_t *susp = *list;
    while (susp->next != NULL) {
      susp = susp->next;
    }
    susp->next = thread;
  }
}

