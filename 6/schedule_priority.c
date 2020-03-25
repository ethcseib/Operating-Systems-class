/*
 *Ethan Seiber
 *Date: 03/24/2020
 *File: schedule_priority.c
 *Description: This file is my implementation of the Priority 
 scheduling algorithm.
 */
#include<stdio.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"
#include <stdlib.h>

/*
 *Function: FindHP
 *Parameters: Takes a pointer to a pointer of type node.
 *Descrition: Finds the higest priority task in the list provided to it via
 the node parameter.
*/
struct node* FindHP(struct node**);


struct node** head;

int check = 0;
int taskID = -1;

//Adds a new task to the linked list.
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

//Schedules the linked list of tasks for execution.
void schedule(){
  
  struct node* highest;
  
  highest = FindHP(head);
  
  printf("Execution of the Highest Priority task:\n");
  while(highest != NULL){
    
    run(highest->task, highest->task->burst);
    free(highest);
    
    if(*head != NULL)
      highest = FindHP(head);
    else
      highest = NULL;
  }
  free(head);
}

struct node* FindHP(struct node** head){
  struct node** highest = (struct node**) malloc(sizeof(struct node));
  struct node* tmp = (struct node*) malloc(sizeof(struct node));
  
  *highest = *head;
  tmp = (*head)->next;
  
  while(tmp != NULL){
    if((*highest)->task->priority < tmp->task->priority){
      *highest = tmp;
    }
    tmp = tmp->next;
  }
  
  delete(head, (*highest)->task);
  tmp = NULL;
  free(tmp);
  return(*highest);
}
