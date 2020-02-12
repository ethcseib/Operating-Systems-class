/**
 *Ethan Seiber and Cody Ginowski
 *Date: 2/12/2020 
 *File: sudoku.c
 *Description: A program that takes a filename containing a 9*9 sudoku table. It checks the table for correctness.
 */
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 *The parameters to be passed to threads
 */
typedef struct{
  int row;
  int column;
  int graph[10][25];
}parameters;

/**
 *Function: ColumnCheck
 *Description: Gets passed to a thread. Checks a column of the sudoku table for correctness.
 */
void* ColumnCheck(void*);

/**
 *Function: RowCheck
 *Description: Gets passed to a thread. Checks a sudoku table row for corectness.
 */
void* RowCheck(void*);

/**
 *Function: SubgridCheck
 *Description: Gets passed to a thread. Checks a 3*3 subgrid of the sudoku table for correctness.
 */
void* SubgridCheck(void*);

/**
 *Function: FillParameters
 *Description: Fills a parameter pointer with a subgrid to be passed to the SubgridCheck.
 */
void FillParameters(parameters*, parameters*);

//Used to determine whether a sudoku table is correct.
int checks = 0;
int main(int argc, char* argv[]){
  
  if(argc == 2){

    FILE* fptr= fopen(argv[1], "r");
    if(fptr != NULL){
    char table[10][25];
    int i = 1;
    parameters* param = (parameters*) malloc(sizeof(parameters));

    while(fgets(table[i], 25, fptr) != NULL){
      i+=1;
    }
    fclose(fptr);
    
    i = 1;
    /**
     *Translates the sudoku table read from the file to integers for future reading.
     */
    for(int j = 0; j < 10; j++){
      for(int k = 0; k < 18; k++){
	if(k%2 == 0){

	  param->graph[j][i] = table[j][k]-'0';
	  i += 1;

	  if(checks != 0){
	    printf("\nThe sudoku table is wrong.\n");
	    exit(0);
	  }
	}
      }
      i = 1;
    }
    
    pthread_t columns;
    pthread_t rows;

    param->row = 1;
    param->column = 1;
    /**
     *This loop performs the rows and columns checks.
     */
    for(int i = 0; i < 9; i++){
      
      pthread_create(&columns, NULL, ColumnCheck,(void*) param);
      pthread_create(&rows, NULL, RowCheck,(void*) param);
      
      pthread_join(columns,NULL);
      pthread_join(rows, NULL);
      
      param->row += 1;
      param->column += 1;
    }

    //An array of threads.
    pthread_t subgrid[10];

    //An array of parameters where each element contains a
    //different subgird of the sudoku table avoiding race conditions.
    parameters* tmp = (parameters*) malloc(10*sizeof(parameters));
    
    param->row = 1;
    param->column = 1;

    //This loop looks at all 9 subgrids and checks for correctness.
    for(int i = 0; i < 9; i++){
      
      FillParameters(tmp, param);

      pthread_create(&subgrid[i], NULL, SubgridCheck, (void*) tmp);
      tmp++;
      
      param->column += 3;
      
      if(param->column >= 9){
	param->column = 1;
	param->row += 3;
      }    
    }
    for(int i = 0; i < 9; i++){
      pthread_join(subgrid[i], NULL);
    }
    if(checks != 0){
	printf("\nThe sudoku table is wrong.\n");
    }
    else{
      printf("The Sudoku table is correct\n");
    }
    free(param);
    //free(tmp);//Cant free memmory.   
    }
    else{
      printf("\nThe file provided doesn't exist\n");
    }
  }

  else{
    printf("\nThere was a problem with the number of command line arguments provided.\n");
  }
  exit(0);
}

/**                                                                                                     
 *Function: FillParameters                                                                              
 *Description: Fills a parameter pointer with a subgrid to be passed to the SubgridCheck.               
 */
void FillParameters(parameters* fill, parameters* with){

  fill->row = 0;
  fill->column = 0;
 
  for(int x = 0; x < 4; x++)
    for(int y = 0; y < 4; y++){
      fill->graph[x][y] = with->graph[with->row + x][with->column + y];
    }
}

/**                                                                                                     
 *Function: ColumnCheck                                                                                
 *Description: Gets passed to a thread. Checks a column of the sudoku table for correctness.
 */
void* ColumnCheck(void* param){

  parameters* param1 = param;
  int* arr = (int*) malloc(10*sizeof(int));

  for(int i = 0; i < 10; i++){
    arr[i] = 0;
  }

  for(int i = 1; i < 10; i++){

    if(arr[param1->graph[i][param1->column]] != 2){

      arr[param1->graph[i][param1->column]] = 2;
    }
    else{
      checks = 1;
    }
  }
  free(arr);
}

/**                                                                                                     
 *Function: RowCheck                                                                                    
 *Description: Gets passed to a thread. Checks a sudoku table row for corectness.                       
 */
void* RowCheck(void* param){

  parameters *param1 = param;
  int arr[10];

  for(int i = 0; i < 10; i++){
    arr[i] = 0;
  }

  for(int i = 1; i < 10; i+=1){

      if(arr[param1->graph[param1->row][i]] != 2){

	arr[param1->graph[param1->row][i]] = 2;
      }
      else{
	
        checks = 1;
      }
  }
}

/**                                                                                                     
 *Function: FillParameters                                                                              
 *Description: Fills a parameter pointer with a subgrid to be passed to the SubgridCheck.               
 */
void* SubgridCheck(void* tmp){

  parameters* param = tmp;
  int arr[10];

  for(int i = 0; i < 10; i++){
    arr[i] = 0;
  }
 
  for(int x = param->row; x < param->row + 3; x++){
    for(int y = param->column; y < param->column + 3; y++){

      if(arr[param->graph[x][y]] != 2){
	
        arr[param->graph[x][y]] = 2;
      }
      else{
	checks = 1;
      }
    }
  }
}
