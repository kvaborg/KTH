#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//#define PAGESIZE (1)
#define PAGESIZE (64)
//#define PAGESIZE (4*1024)

//#define PAGES 64
//#define PAGES 128
//#define PAGES (32*1024)
#define PAGES (4*1024) 
// WARNING THIS MIGHT BE TOO LARGE
//#define PAGES (1024*1024) 

#define REFS (10 * 1024 * 1024)

int main(int argc, char *argv[]) {
  clock_t c_start, c_stop;
  
  char *memory = malloc((long)PAGESIZE * PAGES);

  for (int p = 0; p < PAGES; p++) {
    long ref = (long)p * PAGESIZE;
    /* force the page to be allocated */
    memory[ref] += 1;
  }

  printf("#TLB experiments\n");
  printf("# page size = %d bytes\n", (PAGESIZE));
  printf("# max pages = %d\n", (PAGES));
  printf("# total number of references = %d Mi\n", (REFS / (1024 * 1024)));
  printf("# pages\t proc\t sum\n");

  
  for (int pages = 4; pages <= PAGES; pages*=2) {
    int loops = REFS / pages;

    c_start = clock();

    long sum = 0;

    for (int l = 0; l < loops; l++) {
      for (int p = 0; p < pages; p++) {
        /* dummy operations */
        //long ref = (long)p * PAGESIZE;
        //sum += memory[ref];
        sum++;
      }
    }

    c_stop = clock();

    double proc;

    proc = ((double)(c_stop - c_start)) / CLOCKS_PER_SEC;

    printf("%d\t %.6f\t %ld\n", pages, proc, sum);
  }
  return 0;
}
