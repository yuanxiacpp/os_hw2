#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>

#include "buffer.h"

//pre-defined buffer size
#define BUFFER_SIZE 20

Buffer buffer(BUFFER_SIZE);


//empty full semaphore
sem_t empty;
sem_t full;

//to control the while loop of producer and consumer
int runtest;


//the elements will be put into buffer, just increament each time for simplification
int element = 1;

sem_t elem_lock;

//act as a consumer
void* consumerThread(void *arg) {
  int c = *((int *)arg);
  while (runtest) {
    sem_wait(&full);
    
    buffer.get(c);

    sem_post(&empty);
    usleep(1000*100);
  }
  return NULL;
}

//act as a producer
void* producerThread(void* arg) {
  int p = *((int *)arg);
  while (runtest) {
    sem_wait(&empty);


    //make sure that each thread generate unique elem
    sem_wait(&elem_lock);
    buffer.put(element++, p);
    sem_post(&elem_lock);
    

    sem_post(&full);
    usleep(1000*100);
  }
  return NULL;
}

int main(int argc, char **argv) {
  
  if (argc != 3) {
    printf("Usage: ./bufferTest NumOfProducer NumOfComsumer\n");
    return 0;
  }

  //get numOfProducers and numOfConsumers from user
  int p_num = atoi(argv[1]);
  int c_num = atoi(argv[2]);

  printf("# of producer: %d, # of consumer: %d\n", p_num, c_num);

  runtest = 1;

  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);
  sem_init(&elem_lock, 0, 1);

  //create producer threads
  for (int i = 0; i < p_num; i++) {
    pthread_t t;
    int *arg = (int *)malloc(sizeof(int));
    *arg = i + 1;
    pthread_create(&t, NULL, &producerThread, (void*)arg);
  }

  //create consumer threads
  for (int i = 0; i < c_num; i++) {
    pthread_t t;
    int *arg = (int *)malloc(sizeof(int));
    *arg = i + 1;
    pthread_create(&t, NULL, &consumerThread, (void*)arg);
  }

  //wait for 5s
  usleep(5*1000*1000);
  
  //terminate producers' and consumers' while loop
  runtest = 0;

  return 0;
}
