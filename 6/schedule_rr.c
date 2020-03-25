/*
 *Ethan Seiber
 *Date: 03/24/2020
 *File: schedule_rr.c
 *Description: This file when compiled is used to run the Round Robbin 
 scheduling algorithm.
*/
#include<stdio.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"
#include <stdlib.h>

/*
 *Function: MoveCell
 *Parameters: Takes two node objects where the first is a linked list 
 while the second is a single task.
 *Description: Moves the cell/task that is provided in the second parameter
 to the end of the linked list provided in the first parameter.
*/
void MoveCell(struct node**, struct node*);

/*
 *Funtion: ReverseList
 *Parameters: Takes a pointer to a pointer of type node.
 *Description: Takes the link list provided in the parameter and reverses it.
 */
void ReverseList(struct node**);

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

//Schedules the linked list for execution
void schedule(){
  
  int units = 10;
  
  ReverseList(head);
  
  struct node* cell;
  
  cell = *head;
  
  printf("Execution of the Round Robbin algorithm:\n");
  
  while(cell != NULL){
    
    if(cell->task->burst - 10 < 0)
      units = cell->task->burst;
    else
      units = 10;
    
    run(cell->task, units);
    
    cell->task->burst -= units;
    
    if(*head != NULL)
      MoveCell(head, cell);
    else
      cell = NULL;
    
    cell = *head;
  }
  free(head);
}

void MoveCell(struct node** head, struct node* cell){
  
  if(cell->task->burst != 0){
    struct node* tmp = (*head)->next;
    
    while(tmp->next != NULL){
      tmp = tmp->next;
    }
    
    delete(head, cell->task);
    cell->next = NULL;
    tmp->next = cell;
  }
  else{
    
    delete(head, cell->task);
    free(cell);
  }
}

void ReverseList(struct node** head){
  
  struct node** tmp = (struct node**) malloc(sizeof(struct node));
  struct node* tmp1;
  
  *tmp = *head;
  delete(head, (*head)->task);
  (*tmp)->next = NULL;
  
  while(*head != NULL){
    tmp1 = *head;
    *head = (*head)->next;	
    tmp1->next = *tmp;
    *tmp = tmp1;	
  }
  tmp1 = *head;
  free(tmp1);
  
  *head = *tmp;
}
