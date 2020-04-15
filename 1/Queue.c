#include "Queue.h"
#include <string.h>
#include <stdio.h>
#include "GlobalVars.txt"

void push(struct Queue* que, char** args){
  
  que->queue[que->endQueue] = args;
  que->size += 1;
  que->endQueue += 1;
}

char** pop(struct Queue* que){
  
  char** tmp = que->queue[0];
  for(int i = 1; i < que->endQueue; i++){

    que->queue[i-1] = que->queue[i];
  }
  que->size -= 1;
  que->queue[que->endQueue] = 0;
  que->endQueue -= 1;

  return tmp;
}

void pushPid(struct QueuePid* queue, pid_t* pid){
  
  queue->queue[queue->endQueue] = pid;
  queue->size += 1;
  queue->endQueue += 1;
}

pid_t* popPid(struct QueuePid* que){
  
  pid_t* tmp = que->queue[0];
  for(int i = 1; i < que->endQueue; i++){

    que->queue[i-1] = que->queue[i];
  }
  que->size -= 1;
  que->queue[que->endQueue] = 0;
  que->endQueue -= 1;

  return tmp;
}
