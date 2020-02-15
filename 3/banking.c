#define N 100
typedef int semaphore;
semaphore mutex = 1;
semaphore empty = N;
semaphore full = 0;

#include<pthread.h>
#include<stdio.h>
#include<unistd.h>//needed for usleep

int balance = 0;

void* Withdraw(void*);
void* Deposit(void*);

int main(int argc, char* argv[]){

pthread_t th[4];

for(int i = 0; i < 4; i++){

    if(i < 2){
pthread_create(&th[i], NULL, Deposit, (void*)&th[i]);
}
    else{
      pthread_create(&th[i], NULL, Withdraw, (void*)&th[i]);
    }
}

for(int i = 0; i < 4; i++){
pthread_join(th[i], NULL);
}
}

void* Withdraw(void* tid){

  int* tmp = (int*) tid;
  
  for (int i=0; i<10; i++){
    if(mutex == 1 && balance >= 10){//test
      //crit reg starts
      full -= 1;
      mutex -= 1;
      int readbalance = balance;
printf("At time %d, the balance for withdrawal thread %d is %d\n", i, *tmp, balance);
      readbalance -= 10;
      usleep(1);
      balance = readbalance;
printf("At time %d, the balance after withdrawal thread %d is %d\n\n", i, *tmp, balance);
      
      //exit crit
      mutex += 1;
      empty += 1;
    }  
    usleep(1); 
  } 
}

void* Deposit(void* tid){
  
  int* tmp = (int*) tid;
  for (int i=0; i<10; i++){
    //enter crit
    if(mutex == 1){//test
    empty -= 1;
    mutex -= 1;

    int readbalance = balance;
printf("At time %d, the balance before depositing thread %d is %d\n", i, *tmp, balance);
    readbalance += 11;
    usleep(10);
    balance = readbalance;
printf("At time %d, the balance after depositing thread %d is %d\n\n", i, *tmp, balance);

    //exit crit
    mutex += 1;
    full += 1;
    }
    usleep(10);
  }
}
