/*                                                                            
 *Ethan Seiber                                                                
 *Date: 03/24/2020                                                            
 *File: schedule_fcfs.c                                                       
 *Description: This file contains the implementation for the                  
 First Come First Serve scheduling algorithm.                                 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

#define SIZE    100

struct node** head;

//Used for assigning the task id's.
int tid = 0;

//Makes sure that when head is first used it only has space allocated once.
int check = 0;

//The current task id to be assigned before a 1 is added.
int taskID = -1;

//Add a new task to the list
void add(char* name, int priority, int burst){

  if(check == 0){
    check ++;
    head = (struct node**) malloc(sizeof(struct node));
    *head = NULL;
    
  }
  Task* task = (Task*) malloc(sizeof(Task));
  
  task->name = name;
  task->tid = (int)__sync_add_and_fetch(&taskID, 1);
  task->priority = priority;
  task->burst = burst;
  
  insert(head, task);
  
}

//schedule the list of tasks for execution using FCFS.
void schedule(){
  struct node** beg = (struct node**) malloc(sizeof(struct node));
  struct node* tmp;
  
  *beg = *head;
  *head = (*head)->next;
  (*beg)->next = NULL;
  
  while(*head != NULL){
    
    tmp = *beg;
    *beg = *head;
    *head = (*head)->next;
    (*beg)->next = tmp;
    
  }
  
  printf("The execution of the FCFS algorithm:\n");
  while(*beg != NULL){
    tmp = *beg;
    run((*beg)->task, (*beg)->task->burst);
    delete(beg, (*beg)->task);
    
    free(tmp);
  }
  *head = NULL;
  
  free(head);
  
}
