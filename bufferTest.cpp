#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>

#include "buffer.h"

#define BUFFER_SIZE 100

Buffer buffer(BUFFER_SIZE);

sem_t empty;
sem_t full;

int runtest = 0;

//Counter


extern "C" void * 
consumerThread(void *arg) {
  while (runtest) {
    sem_wait(&full);

    printf("consume %d\n", buffer.get());

    sem_post(&empty);
  }
  return NULL;
}

extern "C" void *
producerThread(void *arg) {
  while (runtest) {
    sem_wait(&full);
    
    srand(time(NULL));
    int product = rand() % 1000;
    buffer.put(product);

    sem_post(&empty);
  }
  return NULL;
}

int main(int argc, char **argv) {
  
  if (argc != 3) {
    printf("Usage: ./bufferTest NumOfProducer NumOfComsumer\n");
    return 0;
  }

  int p_num = atoi(argv[1]);
  int c_num = atoi(argv[2]);

  printf("# of producer: %d, # of consumer: %d\n", p_num, c_num);

  
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
  runtest = 1;

  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);

  for (int i = 0; i < p_num; i++)
    pthread_create(NULL, &attr, producerThread, NULL);
  for (int i = 0; i < c_num; i++)
    pthread_create(NULL, &attr, consumerThread, NULL);

  //wait for 5s
  usleep(5*1000*1000);
  
  runtest = 0;

  return 0;
}
