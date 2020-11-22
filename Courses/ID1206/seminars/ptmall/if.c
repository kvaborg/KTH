#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (atoi(argv[1]) == 0) {
    printf("0");
  }
  if (atoi(argv[1]) == 1) {
    printf("1");
  } else {
    printf("2");
  }
}
