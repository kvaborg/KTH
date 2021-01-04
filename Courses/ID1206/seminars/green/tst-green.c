#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "green.h"

void *testA(void *arg) {
  int i = *(int*)arg;
  int loop = 4;
  while (loop > 0) {
    printf("thread %d: %d\n", i, loop);
    loop--;
    green_yield();
  }
  return NULL;
}

void *testB(void *arg) {
  printf("TEST B\n");
  int *ret = (int *)malloc(sizeof(int));
  *ret = *(int*)arg + 3;
  printf("Return value TestB: %d\n", *ret);
  return ret;
}

int main() {
  green_t g0, g1, g2;

  int *retval_b = NULL;

  int a0 = 0;
  int a1 = 1;
  int a2 = 2;

  green_create(&g0, testA, &a0);
  green_create(&g1, testA, &a1);
  green_create(&g2, testB, &a2);

  green_join(&g0, NULL);
  green_join(&g1, NULL);
  green_join(&g2, (void **)&retval_b);

  //assert(retval_b != NULL);

  printf("retvalB: %d\n", *retval_b);

  free(retval_b);
  
  printf("done\n");
  return 0;
}
