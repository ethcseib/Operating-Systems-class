/*Ethan Seiber & Cody
 *File: shell.c
 *Date: 04/02/2020
 *Description: This is a shell that will execute any commands if they exist.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "GlobalVars.txt"
#include "Queue.h"

/*Function: ParseByNewlineSemiColon
 *This function will take an int as a parameter to count the number of commands
 *to be executed concurrently. It will also take a c-string and return a 2D
 *char array where each 2nd dimension index is a c-string with a command.
 */
char** ParseByNewlineSemiColon(int*, char*);

/*Function: ParseBySpace
 *This function takes a c-string and will tokenize it using the regular 
 *expression space. It returns a 2D char array where each each 2nd dimension
 *index is a c-string with a command or command options.
 */
char** ParseBySpace(char*);

int main (int argc, char* argv[]){
  
  if(argc == 2){
    /*This is the code for batch mode. It will open the file passed in and read
     *the commands from the file and execute them. It uses queues to store 
     *commands to be executed. This allows them to be executed concurrently. 
     *Problem: If a command is mis-typed then this will cause problems for the
     *shell.
     */ 
    struct Queue *queue = (struct Queue*) malloc(sizeof(struct Queue));
    struct QueuePid* queuePid = (struct QueuePid*) malloc(sizeof(struct QueuePid));
    FILE *fptr = NULL;
    char** commandArr;
    char commandStr[SIZE];
    char** args;
    int err = 0;
    int* count = (int*) malloc(sizeof(int));
    
    fptr = fopen(argv[1], "r");

    if(fptr != NULL){
      
      while(fgets(commandStr, SIZE-1, fptr) != NULL){
       
	commandArr = ParseByNewlineSemiColon(count, commandStr);
	
	for(int j = 0; j < *count; j++){
 	  
	  printf("\n\nPreparing to execute command: %s\n\n", commandArr[j]);
	  args = ParseBySpace(commandArr[j]);

	  /*This function will push the c-string into a queue for concurrent
	   *execution of commands.
	   */
	  push(queue, args);
	}
        
	char** arguments;
        
	pid_t* pid = (pid_t*) malloc(sizeof(pid_t));
        int stat;
	while(queue->size != 0){
	  arguments = pop(queue);
	  
	  if((*pid = fork()) == 0){
	    err = execvp(arguments[0], arguments);
	  }	
	  if(err == -1){
	    printf("\nA command does not exist or cannot be executed.\n");
	    exit(0);
	  }

	  if(err == 0){

	    /*This function will push the child process identifier into a queue
	     *that will be used to wait for the completion of the child 
	     *processes
	     */
	    pushPid(queuePid, pid);
	    pid = (pid_t*) malloc(sizeof(pid_t));
	  }
	  else{
	    err = 0;
	  }
	}
	while(queuePid->size != 0){
	  /*This loop will execute waitpid for all queued child processes.
	   */
	  waitpid(*popPid(queuePid), &stat, 0);
	}
      }
    }
    free(queuePid);
    fclose(fptr);
    free(args);
    free(commandArr);
    free(count);
    free(queue);
    
    exit(0);
  }

  else{
    /*This is for the interactive mode portion of the assignment. It takes 
     *input from the user and if it is a valid command will execute it. This 
     *mode also uses queues for command execution. This again will allow for 
     *concurrent executions of commands.
     */
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    struct QueuePid* queuePid = (struct QueuePid*) malloc(sizeof(struct Queue));
    pid_t* pid = (pid_t*) malloc(sizeof(pid_t));
    char** args;
    char* userInput = (char*) malloc(SIZE*sizeof(char));
    char** commandList;
    int err = 0;
    int cont = 0;
    int* count = (int*) malloc(sizeof(int));

    printf("INPUT: ");

    while(cont == 0){
      
      fgets(userInput, SIZE-1, stdin);
      
      if(strcmp(userInput, "quit\n") == 0 || strcmp(userInput, "Quit\n") == 0
	 || strcmp(userInput, "q\n") == 0 || strcmp(userInput, "Q\n") == 0){
	
	exit(0);
      }
      
      commandList = ParseByNewlineSemiColon(count, userInput);

      for(int j = 0; j < *count; j++){
	printf("Preparing to execute command: %s\n", commandList[j]);
	args = ParseBySpace(commandList[j]);                             

	/*This function is pushing commands into a queue in order for concurrent
	 *execution of commands to be possible.
	 */
	push(queue, args);
      }

      char** arguments;
      while(queue->size != 0){
	
	arguments = pop(queue);
        
	if((*pid = fork()) == 0){
	  err = execvp(arguments[0], arguments); 
	}
	if(err == -1){
	  printf("\nA command does not exist or cannot be executed.\n");
	  exit(0);
	}

	if(err == 0){

	  /*This function pushes the identifiers for child processes into a 
	   *to be used with a wait system call.
	   */
	  pushPid(queuePid, pid);
	  pid = (pid_t*) malloc(sizeof(pid_t));
	}
	else{
	  err = 0;
	}
      }
      int stat;
      while(queuePid->size != 0){

	/*This function will call wait for each child process that was created
	 */
	waitpid(*popPid(queuePid), &stat, 0);
      }
      printf("\nINPUT: ");
    }
    free(args);
    free(queue);
    free(queuePid);
  }
   
  exit(0);
}

char** ParseByNewlineSemiColon(int* count, char* commands){
  /*As explained earlier this function will tokenize a c-string by newline and
   *semicolon characters. It will also count the number of commands to be 
   *executed concurrently. This function returns the tokenized string in the 
   *form of a 2D char array.
   */
  char* token;
  char character[2] = "\n";
  char** args = (char**) malloc(SIZE*SIZE*sizeof(char));
  char** commandList = (char**) malloc(SIZE*SIZE*sizeof(char));
  
  int i = 1;

  token = strtok(commands, character);
  commandList[0] = token;
  while(token != NULL){
    token = strtok(NULL, character);
    commandList[i] = token;
    i += 1;
  }

  character[0] = ';';

  i = 1;
    token = strtok(commandList[0], character);
    args[0] = token;
    *count = 0;
    while(token != NULL){
      
      token = strtok(NULL, character);
      args[i] = token;
      i += 1;
      *count += 1;
    }
  
  free(commandList);
  free(token);

  return(args);
}
char** ParseBySpace(char* commands){

  /*This function takes a c-string and tokenizes it by the space character. It 
   *returns the tokens in the form of a 2D char array.
   */
  char ** args = (char**) malloc(SIZE*SIZE*sizeof(char));
  char tmp[2];
  char* token;

  tmp[0] = ' ';
  
  token = strtok(commands, tmp);
  args[0] = token;
  
  int i = 0;
  while(token != NULL){

    i += 1;
    token = strtok(NULL, tmp);
    args[i] = token;
  }
    
  free(token);
  
  return(args);
}
