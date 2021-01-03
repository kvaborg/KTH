#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "green.h"
#include "queue.h"

int flag = 0;
green_cond_t cond;

int fib(int num) {
  if(num <= 1) {
    return num;
  } else {
    return fib(num - 1) + fib(num - 2);
  }
}

void hold() {
  struct timespec start, finish;

  clock_gettime(CLOCK_MONOTONIC, &start);
  
  while(finish.tv_nsec - start.tv_nsec < 4000000) {
    clock_gettime(CLOCK_MONOTONIC, &finish);
  }
  return;
}

void *test(void *arg) {
  int id = *(int *)arg;
  int loop = 4;
  while(loop > 0) {
    if (flag == id) {
      printf("thread %d: %d\n", id, loop);
      loop--;
      flag = (id + 1) % 2;
      //int f = fib(20);
      //printf("dummy: %i\n", f);
      hold();
      green_cond_signal(&cond);
    } else {
      green_cond_wait(&cond);
    }
  }
  return NULL;
}

int main() {

  green_cond_init(&cond);
  green_t g0, g1;

  int a0 = 0;
  int a1 = 1;

  green_create(&g0, test, &a0);
  green_create(&g1, test, &a1);

  green_join(&g0, NULL);
  green_join(&g1, NULL);
  
  printf("done\n");
  return 0;
}


