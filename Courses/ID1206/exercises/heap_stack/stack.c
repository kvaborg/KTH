#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void zot(unsigned long *stop) {
  unsigned long r = 0x3;

  unsigned long *i;
  for(i = &r; i <= stop; i++) {
    printf("%p 0x%lx\n", i, *i);
  }
}

//Add dummy args to print args on stack
void foo(unsigned long *stop, int a, int b, int c, int d, int e, int f, int g, int h, int j, int k) {
  unsigned long q = 0x2;
  zot(stop);
}

int main() {
  int pid = getpid();
  unsigned long p = 0x1;

  foo(&p, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5);
  
  back:
    printf("p: %p\n", &p);
    printf("back: %p\n", &&back);
    printf("pid in hex: %x\n", pid);
    
    printf("\n\n /proc/%d/maps \n\n", pid);
    char command[50];
    sprintf(command, "cat /proc/%d/maps", pid);
    system(command);

    return 0;
}
