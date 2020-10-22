#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "common.h"

void spin(int sec) {
  int msec = 0, trigger = sec * 1000; /* 1 sec */ 
  clock_t before = clock();

  do {
    clock_t diff = clock() - before;
    msec = diff * 1000 / CLOCKS_PER_SEC;
  } while(msec < trigger);
}
