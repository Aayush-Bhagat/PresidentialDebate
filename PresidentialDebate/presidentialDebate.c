#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

static sem_t connected_lock;
static sem_t operators;
static int NUM_OPERATORS = 2;
static int NUM_LINES=5;
static int connected = 0;
int next_id = 1;

void *phonecall(void* vargp){
  int ID = (int) vargp;
  printf("THREAD %i is attempting to connect...\n", ID);
  int connection = 0;
  while(connection == 0){
   sem_wait(&connected_lock);
   if(connected < NUM_LINES){ 
     connected++;
     sem_post(&connected_lock);
     break;
      
   }
   if(connected >= 5){
     sem_post(&connected_lock);
     sleep(1);
   }
  }
  printf("THREAD %i connects to an avaiblabe line, call ringing...\n", ID);
  sem_wait(&operators);
  printf("THREAD %i is speaking to an operator\n", ID);
  sleep(1);
  printf("THREAD %i has proposed a question for candidates! the operator has left...\n", ID);
  sem_post(&operators);
  sem_wait(&connected_lock);
  connected--;
  sem_post(&connected_lock);
  printf("THREAD %i has hung up!\n", ID);
}

void *timer(void* vargp){
  int time= (int) vargp;
  sleep(time); 
}

int main(int argc, char* argv[]) {
 pthread_t threadIDs[200]; 
 sem_init(&operators, 0, NUM_OPERATORS);
 sem_init(&connected_lock, 0, 1);
 if(argc < 2){
   printf("Please try again and input a proper time for the debate\n");
   exit(0);
 } 
 
 for(int i =0; i <200; i++){
  pthread_create(&threadIDs[i], NULL, phonecall, (void*) next_id);
  next_id++;  
 }
 
 pthread_t timerThread;
 int time = atoi(argv[1]);
 pthread_create(&timerThread, NULL, timer, (void *) time);
 pthread_join(timerThread, NULL);
 sem_destroy(&connected_lock);
 sem_destroy(&operators);
 exit(0);
 return 0;
}
