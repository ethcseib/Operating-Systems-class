#include<pthread.h>
#include<stdio.h>
#include<unistd.h>//needed for usleep

/**                                                                            
 *Name: Ethan Seiber                                                           
 *Date: 2/15/2020                                                              
 *File: banking.c                                                              
 *Description: Practice with mutual exclusion through a very simple            
 *banking application.                                                         
 */

//The program mutex, sleep and wake condition and the balance of the account.
pthread_mutex_t the_mutex;
pthread_cond_t condW;
int balance = 0;

/**
 *Function: Withdraw
 *A banking withdraw function. Will withdraw $10 unless the balance is less 
 *than or equal to $10. This function is to be passed to a thread.
 */
void* Withdraw(void*);

/**
 *Function: Deposit
 *A banking deposit function. This function will deposit $11 into the balance.
 *This function is to be passed to a thread. 
 */
void* Deposit(void*);

int main(int argc, char* argv[]){

  //Thread, mutex, and condition creation.
  pthread_t th[4];
  pthread_mutex_init(&the_mutex, NULL);
  pthread_cond_init(&condW, NULL);
  
  for(int i = 0; i < 4; i++){
    
    if(i < 2){
      pthread_create(&th[i], NULL, Withdraw, (void*)&th[i]);
    }
    else{
      pthread_create(&th[i], NULL, Deposit, (void*)&th[i]);
    }
  }
  
  for(int i = 0; i < 4; i++){
    pthread_join(th[i], NULL);
  }
  
  //mutex and condition destruction
  pthread_mutex_destroy(&the_mutex);
  pthread_cond_destroy(&condW);
  
  printf("\nThe final balance is %d\n", balance);
  return(0);
}

void* Withdraw(void* tid){
  
  int* tmp = (int*) tid;
  
  for (int i=0; i<10; i++){
    pthread_mutex_lock(&the_mutex);
    
    if(balance <= 10){
      printf("\n\nBlocking thread because balance is %d\n\n", balance);
      pthread_cond_wait(&condW, &the_mutex);
    }

    int readbalance = balance;

    printf("At time %d, the balance for withdrawal thread %d is %d\n", i, *tmp, balance);

    readbalance -= 10;

    usleep(1);

    balance = readbalance;

    printf("At time %d, the balance after withdrawal thread %d is %d\n\n", i, *tmp, balance);
    
    //exit crit
    pthread_mutex_unlock(&the_mutex);

    usleep(1); 
  } 
}

void* Deposit(void* tid){
  
  int* tmp = (int*) tid;

  for (int i=0; i<10; i++){
    //enter crit
    pthread_mutex_lock(&the_mutex);
    
    int readbalance = balance;

    printf("At time %d, the balance before depositing thread %d is %d\n", i, *tmp, balance);
    
    if(balance >= 10){
      printf("\n\nWaking up withdraw threads because balance is %d\n\n", balance);
      pthread_cond_signal(&condW);
    }
    readbalance += 11;

    usleep(10);

    balance = readbalance;

    printf("At time %d, the balance after depositing thread %d is %d\n\n", i, *tmp, balance);
    
    //exit crit
    pthread_mutex_unlock(&the_mutex);
    
    usleep(10);
  }
}
