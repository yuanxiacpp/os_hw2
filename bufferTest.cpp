#include <pthread.h>
#include <thread.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <sched.h>

#include "buffer.h"

#define BUFFER_SIZE 10

Buffer buffer(BUFFER_SIZE);



pthread_mutex_t mutex;

//Counter
int produceCounter = 0;
int consumeConter = 0;


extern "C" void * 
consumerThread(void *arg) {
  while (runtest) {

  }
  return NULL;
}

extern "C" void *
producerThread(void *arg) {
  while (runtest) {
    
  }
  return NULL;
}

int main(int argc, char **argv) {
  
  if (argc != 3) {
    printf("Usage: ./bufferTest NumOfProducer NumOfComsumer\n");
    return 0;
  }
  
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

  int p_num = atoi(argv[1]);
  int c_num = atoi(argv[2]);

  runtest = 1;

  for (int i = 0; i < p_num; i++)
    pthread_create(NULL, &attr, producerThread, NULL);
  for (int i = 0; i < c_num; i++)
    pthread_create(NULL, &attr, consumerThread, NULL);

  for (int i = 0; i < 20; i++) {
    usleep(1*1000*1000);
    printf("amount_of_produce=%d\n", produceCounter);
    printf("amount_of_consume=%d\n", consumeConter);
    printf("------------------\n");
  }

  runtest = 0;

  return 0;
}
