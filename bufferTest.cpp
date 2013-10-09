#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>

#include "buffer.h"

#define BUFFER_SIZE 20

Buffer buffer(BUFFER_SIZE);

sem_t empty;
sem_t full;

int runtest = 0;

int element = 1;

//Counter


void* consumerThread(void*) {
  while (runtest) {
    sem_wait(&full);
    
    buffer.get();

    sem_post(&empty);
    usleep(1000*100);
  }
  return NULL;
}

void* producerThread(void*) {
  while (runtest) {
    sem_wait(&empty);

    buffer.put(element++);

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

  int p_num = atoi(argv[1]);
  int c_num = atoi(argv[2]);

  int element = 1;

  printf("# of producer: %d, # of consumer: %d\n", p_num, c_num);

  runtest = 1;

  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);

  for (int i = 0; i < p_num; i++) {
    pthread_t t;
    pthread_create(&t, NULL, &producerThread, NULL);
  }
  for (int i = 0; i < c_num; i++) {
    pthread_t t;
    pthread_create(&t, NULL, &consumerThread, NULL);
  }

  //wait for 5s
  usleep(5*1000*1000);
  
  runtest = 0;

  return 0;
}
