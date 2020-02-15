#include<ptrhead.h>
#include<stdio.h>

struct bank{
  int balance;
};

void* Withdraw(void*);
void* Deposit(void*);

int main(int argc, char* argv[]){

  pthread_t with1;
  pthread_t with2;
  pthread_t dep1;
  pthread_t dep2;

  
}

void* Withdraw(void* tmp){
  struct bank* bnk = tmp;
  bnk->balance -= 10;
}

void* Deposit(void* tmp){
  struct bank* bnk = tmp;
  bnk += 11;
}
