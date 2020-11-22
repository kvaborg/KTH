#include "dlmall.h"
#include <stdio.h>

#define MIN(size) (((size) > (8))?(size):(8))

int main() {
  struct head *arena = new_arena();
  dfree(arena);
  sanity();

//  detach(arena);
//  sanity();
  char *mem;
  mem = (char *)dalloc(8);
  sanity();
  dfree(mem);
//
//  sanity();

  return 0;
}
