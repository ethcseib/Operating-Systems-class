#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
  int row;
  int column;
  int graph[10][25];
}parameters;

void* ColumnCheck(void*);
void* RowCheck(void*);
void* SubgridCheck(void*);
void FillParameters(parameters*, parameters*);

int checks = 0;
int main(int argc, char* argv[]){
  
  if(argc > 1){
    FILE* fptr = fopen(argv[1], "r");
    char table[10][25];
    int i = 1;
    parameters* param = (parameters*) malloc(sizeof(parameters));

    while(fgets(table[i], 25, fptr) != NULL){
      i+=1;
    }
    fclose(fptr);
    
    i = 1;
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
    
    for(int i = 0; i < 9; i++){
      
      pthread_create(&columns, NULL, ColumnCheck,(void*) param);
      pthread_create(&rows, NULL, RowCheck,(void*) param);
      
      pthread_join(columns,NULL);
      pthread_join(rows, NULL);
      
      param->row += 1;
      param->column += 1;
    }
    
    pthread_t subgrid[10];
    parameters* tmp = (parameters*) malloc(10*sizeof(parameters));
    
    param->row = 1;
    param->column = 1;
    
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
  exit(0);
}

void FillParameters(parameters* fill, parameters* with){

  fill->row = 0;
  fill->column = 0;
 
  for(int x = 0; x < 4; x++)
    for(int y = 0; y < 4; y++){
      fill->graph[x][y] = with->graph[with->row + x][with->column + y];
    }
}

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
