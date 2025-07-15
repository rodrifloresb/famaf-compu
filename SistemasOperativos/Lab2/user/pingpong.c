#include "kernel/types.h"
#include "user.h"
#include <stdbool.h>

#define MAX_SEMS 64

void ping_pong(int sem1, int sem2, bool is_ping, int n){
  while(n>0){
    sem_down(sem1);
    if(is_ping){
      printf("ping \n");
    } else{
      printf("    pong \n\n");
    }
    --n;
    sem_up(sem2);
  }
}

int main(int argc, char *argv[]){

  int n = atoi(argv[1]);

  if(argc != 2 || n == 0){
    printf("ERROR! usage: pingpong N (N > 0) \n");
    exit(1);
  }

  int sem_ping = sem_open(0, 1);
  int sem_pong = sem_open(1, 0);

  if(fork() == 0){
    ping_pong(sem_pong, sem_ping, false, n);
  } else {
    ping_pong(sem_ping, sem_pong, true, n);
    wait(0);
  } 

  sem_close(sem_ping);
  sem_close(sem_pong);

  return 0;
}
