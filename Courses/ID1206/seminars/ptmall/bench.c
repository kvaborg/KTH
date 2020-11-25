#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "dlmall.h"
#include "rand.h"

#define BUFFER 100 // The smaller the buffer, the higher probability that blocks are freed
#define SIZES 10000

int freq[SIZES];

void sizes(int *buffer, int max);

int cmp(const void *a, const void *b) {
  return *(int*)a - *(int*)b;
}

int main(int argc, char *argv[]) {
  int no_of_blocks = atoi(argv[1]);
  char *name1 = argv[2];  
  char *name2 = argv[3];  

  init();

  srand(time(0));

  void *buffer[BUFFER];
  for(int i =0; i < BUFFER; i++) {
    buffer[i] = NULL;
  }

  FILE *file = fopen(name1, "a");

  /* Allocate argv[1] no of blocks of random size between MIN and MAX */

  for (int i = 0; i < no_of_blocks; i++) {
    int index = rand() % BUFFER;
    if(buffer[index] != NULL) {
      dfree(buffer[index]);
    }
    size_t size = (size_t)request();
    int *memory; 
    memory = dalloc(size);

//    if(memory == NULL) {
//      //memory = dalloc(0);	
//      fprintf(stderr, "memory dallocation failed, when tyring to add size: %li", size);
//      return(1);
//    }
    buffer[index] = memory;
    /* writing to the memory so we know it exists */
    // *memory = 123;

    int length = length_of_free();
    fprintf(file, "%d\t%d\n", i, length);
    fflush(file);
  }
  fclose(file);

  /* Get number of blocks in freelist */
  int length = length_of_free();
  sanity();
  printf("No of blocks in freelist: %i\n", length);

  fopen(name2, "w");
  
  sizes(freq, SIZES);

  qsort(freq, length, sizeof(int), cmp); 
  
  for(int i = 0; i < length; i++) {
    fprintf(file, "%d\n", freq[i]);
  }

  fclose(file);
  
//  fopen(strcat(original, "_length.dat"), "w");
//  
  fprintf(file, "%d\t%d", no_of_blocks, length);

  printf("<return> to continue\n");  
  char ch;
  read(STDIN_FILENO, &ch, 1);
  
  return 0;
}

