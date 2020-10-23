#include <stdio.h>  // for fprintf()
#include <stdlib.h>
#include <unistd.h> // for sleep()
#include <pthread.h> 

volatile int counter = 0;

int loops = 0;

void *worker(void *arg) {
  char *name = (char*)arg;

  for(int i = 0; i < loops; i++){
    counter++;
    //printf("Hello %s %d (%p)\n", name, counter, &counter);
    //sleep(2);
  }
  return NULL;
}

int main(int argc, char *argv[]){
  if(argc != 2){
    fprintf(stderr, "usage: threads <loops>\n");
    exit(1);
  }
  
  loops = atoi(argv[1]);

  pthread_t p1, p2;

  pthread_create(&p1, NULL, &worker, "A");
  //sleep(1);
  pthread_create(&p2, NULL, &worker, "B");

  pthread_join(p1, NULL);
  pthread_join(p1, NULL);

  printf(" final value is %d \n", counter);
  return 0;
}
