#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("hello world, (pid:%d)\n", (int) getpid());
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if(rc == 0){
    printf("Hello, I am a child (pid:%d)\n", (int) getpid());
    printf("Hello, I am parent (pid:%d)\n", rc);
  } else {
    printf("Hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
  }

  return 0;
}
