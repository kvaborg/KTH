#include "dlmall.h"
#include <stdio.h>

#define MIN(size) (((size) > (8))?(size):(8))

int main() {
  init();

  char *mem1;
  char *mem2;
  char *mem3;
  char *mem4;

  mem1 = (char *)dalloc(15);
  mem2 = (char *)dalloc(15);
  mem3 = (char *)dalloc(15);
  mem4 = (char *)dalloc(15);

  dfree(mem1);
  dfree(mem3);
  dfree(mem2);

  sanity();

  return 0;
}
