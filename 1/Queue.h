#ifndef QUEUE_H
#define QUEUE_H

#include "GlobalVars.txt"
#include <sys/wait.h>
/**
 *@file Queue.h | Queue.c
 *@author Ethan Seiner
 *@date Jan. 11, 2020
 *@brief The purpose is to create a Queue struct and organize functions related to a Queue in the same file.
 */

/**
 *@struct Queue
 *This struct represents a queue.
 *@author Ethan Seiber
 *@var endQueue: An int that records the index of the end of the queue which is the index after the last element of the queue.
 *@var size: An int that represents the number of elements in the queue.
 *@var queueCap: An unsigned int to represent the capacity of the queue.
 *@var queue: An int array to represent putting data in a queue.
 */
struct Queue{
  int endQueue;
  int size;
  unsigned int queueCap;
  char** queue[SIZE]; 
};

/**
 *@struct QueuePid 
 *This struct represents the data structure queue.
 *@author Ethan Seiber
 **@var endQueue: An int that records the index of the end of the queue which is the index after the last element of the queue.
 *@var size: An int that represents the number of elements in the queue.
 *@var queueCap: An unsigned int to represent the capacity of the queue.
 *@var queue: An int array to represent putting data in a queue.
 */
struct QueuePid{
  int endQueue;
  int size;
  unsigned int queueCap;
  pid_t* queue[SIZE];
};
/**
 *This function takes a Queue and an int and puts it in the Queue.
 *@author Ethan Seiber
 *@param que: A Queue struct pointer for data to be stored.
 *@param num: This is the int that will be stored in the Queue struct.
 *@date Jan. 11, 2020
 *@return Returns nothing because there is no need because the variable being modified is a Queue pointer.
 */
void push(struct Queue* que, char**);

/**
 *This function will remove the int from the beginning of the Queue.
 *@author Ethan Seiber
 *@param que: A Queue pointer that will be modified inside the function.
 *@date Jan. 11, 2020
 *@return Returns an int that is pulled out of the Queue.
 */
char** pop(struct Queue* que);

/**
 *This function will push the pid_t pointer to the end of the queue passed in.
 *@author Ethan Seiber
 *@param QueuePid*: A pointer to the queue to be pushed into.
 *@param pid_t*: The data to be stored in the queue.
 */
void pushPid(struct QueuePid*, pid_t*);

/**
 *This function will pop the value being stored at the beginning of the queue off and return it.
 *@author Ethan Seiber
 *@param QueuePid*: The queue to have data popped from.
 *@return Returns a pid_t* pointer that was pulled from the queue.
 */
pid_t* popPid(struct QueuePid*);
#endif
