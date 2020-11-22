#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

#define _GNU_SOURCE

#define TRUE 1
#define FALSE 0

#define HEAD (sizeof(struct head))
#define MIN(size) (((size) < (8))?(size):(8))
#define LIMIT(size) (MIN(0) + HEAD + size)
#define MAGIC(memory) ((struct head*)memory - 1)
#define HIDE(block) (void *)((struct head*)block + 1)
#define ALIGN 8
#define ARENA (64 * 1024)

struct head {
  uint16_t bfree;
  uint16_t bsize;
  uint16_t free;    
  uint16_t size;
  struct head *next;
  struct head *prev;
};

struct head *after(struct head *block) {
  return (struct head*)((char *)block + HEAD + block->size);
}

struct head *before(struct head *block) {
  return (struct head*)((char *)block - (block->bsize + HEAD));
}

/* TODO */
struct head *split(struct head *block, int size) {
  int rsize = block->size - (size + HEAD);
  block->size = rsize;

  struct head *splt = after(block);
  splt->bsize = block->size;
  splt->bfree = block->free; // FALSE?
  splt->size = size;
  splt->free = FALSE;

  struct head *aft = after(splt);
  aft->bsize  = splt->size;

  return splt;
}

struct head *arena = NULL;

struct head *new() {
  if (arena != NULL) {
    printf("one arena already allocated \n");
    return NULL;
  }

  // using mmap, but could have used sbrk
  struct head *new = mmap(NULL, ARENA, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (new == MAP_FAILED) {
    printf("mmap failed: error %d\n", errno);
    return NULL;
  }

  /* make room for head and dummy */
  unsigned int size = ARENA - 2 * HEAD;

  new->bfree = FALSE;
  new->bsize = 0;
  new->free = TRUE;
  new->size = size;

  struct head *sentinel = after(new);

  /* only touch the status fields */
  sentinel->bfree = new->free;
  sentinel->bsize = new->size;
  sentinel->free = FALSE;
  sentinel->size = 0;

  /* this is the only arena we have */
  arena = (struct head*)new;

  return new;
}

/* create free list */
struct head *flist;

void detach(struct head *block) {
  if (block->next != NULL) {
    block->next->prev = block->prev;
  }
  if (block->prev != NULL) {
    block->prev->next = block->next;
  } else {
    block->next->prev = NULL;
  }
}

void insert(struct head *block) {
  block->next = flist;
  block->prev = NULL;

  if(flist != NULL) {
    flist->prev = block;  
  }

  flist = block;
}

int adjust(size_t request) {

  int newRequestSize = MIN(request);

  /* Adjust request in order to fit with ALIGN */
  if (newRequestSize % ALIGN == 0) {
    return newRequestSize;
  } else {
    int adj = newRequestSize % ALIGN;
    return newRequestSize + adj;
  }

}

struct head *find(int size) {
  if (flist == NULL) {
    return NULL;
  }

  struct head *freelist = flist;
  while (freelist) {
    if (freelist->size >= size) {
      detach(freelist);
      if (freelist->size >= size + HEAD +MIN(0)) {
        struct head *block = split(freelist, size);
        after(block)->bfree = block->prev->free;      
        insert(freelist);
        return block;
      } else {
        return freelist;
      }
    }
  }

  return NULL;
}

void *dalloc(size_t request) {
  if (request <= 0) {
    return NULL;
  }
  int size = adjust(request);
  struct head *taken = find(size);
  if (taken == NULL) {
    return NULL;
  } else {
    return taken;
  }
}

void dfree(void *memory) {
  if (memory != NULL) {
    struct head *block = ...
    struct head *aft = ...
    block->free = ...
    block->bfree = ...
  }
  return;
}
