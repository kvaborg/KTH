#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* the number of datapoints */
#define SAMPLES 20

/* 20% of the pages will have 80% of the hits */
#define HIGH 20
#define FREQ 80

typedef struct Pte {
  int present;
} Pte;

void init(int *sequence, int refs, int pages) {

  int high = (int)(pages * ((float)HIGH / 100));

  for (int i = 0; i < refs; i++) {
    if (rand() % 100 < FREQ) {
      /* the frequently case */
      sequence[i] = rand() % HIGH;
    } else {
      /* the less frequently case */
      sequence[i] = high + rand() % (pages - high);
    }
  }
}

void clear_page_table(Pte *page_table, int pages) {
  for (int i = 0; i < pages; i++) {
    page_table[i].present = 0;
  }
}

int simulate(int *seq, Pte *table, int refs, int frms, int pgs) {

  int hits = 0;
  int allocated = 0;

  for (int i = 0; i < refs; i++) {
    int next = seq[i];

    Pte *entry = &table[next];

    if (entry->present == 1) {
      hits++;
    } else {
      if (allocated < frms) {
        allocated++;
        entry->present = 1;
      } else {
        Pte *evict;
        do {
          int rnd = rand() % pgs;
          evict = &table[rnd];
        } while(evict->present != 1);
        evict->present = 0;
        entry->present = 1;
      }
    }
  }
  return hits;
}

int main(int argc, char *argv[]) {

  /* could be command line args */
  int refs = 100000;
  int pages = 100;

  int *sequence = (int *)malloc(refs * sizeof(int));

  init(sequence, refs, pages);

  Pte *table = (Pte *)malloc(pages*sizeof(Pte));

  printf("# This is a benchmark of random replacement\n");
  printf("# %d page references\n", refs);
  printf("# %d pages\n", pages);
  printf("#\n#\n#frames\tratio\n");

  /* frames is the size of the memory in frames */
  int frames;

  int incr = pages / SAMPLES;

  for (frames = incr; frames <= pages; frames += incr) {
    /* clear page table entries */
    clear_page_table(table, pages);

    int hits = simulate(sequence, table, refs, frames, pages);

    float ratio = (float)hits/refs;

    printf("%d\t%.2f\n", frames, ratio);
  }

  return 0;
}
