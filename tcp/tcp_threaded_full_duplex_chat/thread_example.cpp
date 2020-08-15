#include<iostream>
#include<unistd.h>
#include<pthread.h>
void* helloPrint(void *);
using namespace std;
int main() {
pthread_t tid;
pthread_create(&tid, NULL, helloPrint, (void*)1);
while(1) {
  cout<<"Hello from main"<<endl;
  sleep(2);
}
return 0;
}
void* helloPrint(void *val) {
  long id = (long)val;
  while(1) {
    cout<<"Hello from thread # "<<id<<endl;
    sleep(2);
  }
}
