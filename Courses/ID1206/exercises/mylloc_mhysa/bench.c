#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "rand.h"

#define ROUNDS 100
#define LOOP 100000
#define BUFFER 100

int main() {
  void *buffer[BUFFER];
  for(int i = 0; i < BUFFER; i++) {
    buffer[i] = NULL;
  }

  void *init = sbrk(0);
  void *current;

  printf("The initial topo of the heap is %p.\n", init);

  for(int j = 0; j < ROUNDS; j++) {
    for(int i = 0; i < LOOP; i++) {
      size_t size = (request());
      int *memory;
      memory = malloc(size);
      if(memory == NULL) {
        fprintf(stderr, "malloc failed\n");
        return(1);
      }
      /* writing to the memory so we know it exists */
      // *memory = 123;
      free(memory);
    }
    current = sbrk(0);
    int allocated = (int)((current - init) / 1024);
    printf("%d\n", j);
    printf("The current top of the heap is %p.\n", current);
    printf("increased by %d Kbyte\n", allocated);
  }
  return 0;
}
