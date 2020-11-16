#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int volatile count;

void handler(int sig) {
  printf("signal %d was caught\n", sig);
  exit(1);
  return;
}

int not_so_good() {
  int x = 0;
  return 1 % x;
}

int main() {
  struct sigaction sa;

  int pid = getpid();

  printf("Ok, let's go - I'll catch my own error.\n");

  sa.sa_handler = handler;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);

  sigaction(SIGFPE, &sa, NULL);

  not_so_good();

  printf("Will probably not write this.\n");
  return(0);
}
