#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
  int row;
  int column;
  //int** graph;
  int graph[10][25];
  int check;
}parameters;

void* ColumnCheck(void*);
void* RowCheck(void*);
void* SubgridCheck(void*);

char* FormatGraph(char*);
void Concatenate(char*, char*);

int main(int argc, char* argv[]){

  if(argc > 1){
    FILE* fptr = fopen(argv[1], "r");
    char table[10][25];
    int i = 1;
    parameters *param = (parameters*) malloc(sizeof(parameters));

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

	  if(param->check != 0){
	    printf("\nThe sudoku table is wrong.\n");
	    exit(0);
	  }
	}
      }
      i = 1;
    }
    
    pthread_t columns;
    pthread_t rows;

    /*for(int i = 1; i < 10; i++){
      printf("param->graph[%d][%d] =  %d\n",i,9,param->graph[i][0]);
      }*/

    param->check = 0;
    param->row = 1;
    param->column = 1;
    
    /*for(int i = 0; i < 9; i++){
      
      pthread_create(&columns, NULL, ColumnCheck,(void*) param);
      pthread_create(&rows, NULL, RowCheck,(void*) param);
      
      pthread_join(columns,NULL);
      pthread_join(rows, NULL);
      
      //printf("check %d\n", param->check);
      if(param->check != 0){
	printf("\nThe sudoku table is wrong.\n");
	exit(0);
      }
      param->row += 1;
      param->column += 1;
      }*/
    
    //free(param);

    param->row = 1;
    param->column = 1;
    pthread_t subgrid[10];
    //FILE*fptr = fopen("main.txt", "w");
    FILE* fpt;
    for(int i = 0; i < 9; i++){ //<= 8; i++){

      printf("\n\ncolumn %d row %d\n\n", param->column, param->row);
      printf("double %d", param->column);
      //SubgridCheck((void*) param);
      pthread_create(&subgrid[i], NULL, SubgridCheck, (void*) param);
      //pthread_join(subgrid[i], NULL);
      //SubgridCheck((void*)param);
      param->column += 3;
      
      if(param->column >= 9){
	param->column = 1;
	param->row += 3;
      }

      /*if(param->check != 0){
	printf("\nThe sudoku table is wrong.\n");
	exit(0);
	}*/
    }
    for(int i = 0; i < 9; i++){//<= 8; i++){
      pthread_join(subgrid[i], NULL);
    }

    if(param->check != 0){                                                  
      printf("\nThe sudoku table is wrong.\n");                               
      exit(0);                                                                
    }
    free(param); 
  }  
  exit(0);
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
      param1->check = 1;
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
	
        param1->check = 1;
      }
  }
}

void* SubgridCheck(void* tmp){

  parameters* param = tmp;
  int arr[10];
  //int j = 0;
  FILE* fptr = fopen("chech.txt", "w");
  for(int i = 0; i < 10; i++){
    arr[i] = 0;
  }

  fputs("rows and cols\n",fptr);
  fputc(param->row + '0', fptr);fputs(" ",fptr);fputc(param->column + '0', fptr);
  for(int x = param->row; x < param->row + 3; x++){
    for(int y = param->column; y < param->column + 3; y++){
      fputs(" param ",fptr);fputc(param->graph[x][y] +'0', fptr);
    }fputs("\n",fptr);
  }
  //printf("\n\nbef\n\n");
  for(int x = param->row; x < param->row + 3; x++){
    for(int y = param->column; y < param->column + 3; y++){

      //printf("param->graph[%d][%d] = %d\n",x,y,param->graph[x][y]);
      if(arr[param->graph[x][y]] != 2){
        arr[param->graph[x][y]] = 2;
      }
      else{
	param->check = 1;//param->graph[x][y];
      }
    }
  }
}
