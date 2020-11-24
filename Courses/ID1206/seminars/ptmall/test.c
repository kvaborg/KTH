#include "dlmall.h"
#include <stdio.h>

#define MIN(size) (((size) > (8))?(size):(8))

int main() {
  init();

  char *mem;
  mem = (char *)dalloc(8);
  dfree(mem);

  sanity();

  return 0;
}
