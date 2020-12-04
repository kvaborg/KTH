#include "dlmall.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {

  init();

  clock_t start, end, total;
  int no_of_blocks = 2000;
  void *memory[no_of_blocks];

  start = clock();
  
  for (int i = 0; i < no_of_blocks; i++) {
    memory[i] = dalloc(16);
  }

  end = clock();
  total = end - start;
  printf("Allocation time: %ld\n", (end - start));

  start = clock();

  for (int i = 0; i < no_of_blocks; i++) {
    for (int j = 0; j < no_of_blocks * 10; j++) {
      int *mem = memory[i];
      *mem = j;
    }
  }
  
  end = clock();
  total += end - start;
  printf("Write time: %ld\n", (end - start));
  printf("Total time: %ld\n", total);

  return 0;
}
