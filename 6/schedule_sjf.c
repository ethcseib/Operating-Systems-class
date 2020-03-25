/*
 *Ethan Seiber
 *Date: 03/24/2020
 *File: schedule_sjf.c
 *Description: Runs the Shortest Job First scheduling algorithm.
 */
#include<stdio.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"
#include <stdlib.h>

/*
 *Function: FindSJF
 *Parameters: Takes the head of the list as a parameter.
 *Description: A helper function for finding the shortest job/task to be executed
 */
struct node* FindSJ(struct node**);

struct node** head;

int check = 0;
int taskID = -1;

//Adds a new task to the linked list
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
  
  struct node** shortest = (struct node**) malloc(sizeof(struct node));
  *shortest = FindSJ(head);
  
  printf("Execution of the SJF algorithm:\n");
  while(*shortest != NULL){
    run((*shortest)->task, (*shortest)->task->burst);
    free(shortest);
    
    if(*head != NULL)
      *shortest = FindSJ(head);
    else
      *shortest = NULL;
  }
  
}

struct node* FindSJ(struct node** head){
  
  struct node** shortest = (struct node**) malloc(sizeof(struct node));
  struct node** tmp = (struct node**) malloc(sizeof(struct node));
  
  *shortest = *head;
  *tmp = (*head)->next;
  
  while(*tmp != NULL){
    
    if((*shortest)->task->burst > (*tmp)->task->burst){
      
      *shortest = *tmp;
    }
    *tmp = (*tmp)->next;
  }
  
  delete(head, (*shortest)->task);

  return(*shortest);
}
