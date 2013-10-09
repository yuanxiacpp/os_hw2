#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

Buffer::Buffer(int size) {
  pthread_mutex_init(&mutex, NULL);

  counter = 0;
  buffer_size = size;
  in = 0;
  out = 0;
  content = (int*)malloc(size*sizeof(int));
}

int Buffer::put(int val) {
  pthread_mutex_lock(&mutex);
  int status = -1;

  //srand(time(NULL));
  //int val = rand() % 1000;

  if (counter != buffer_size) {
    printf("Produce %d\n", val);
    content[in] = val;
    in = (in + 1) % buffer_size;
    counter++;
    status = 0;
  }
  //put nothing
  else {
    //just in case
    printf("Buffer full...\n");
  }
  pthread_mutex_unlock(&mutex);
  return status;
}

int Buffer::get() {
  pthread_mutex_lock(&mutex);
  int result = -1;
  if (counter != 0) {
    result = content[out];
    printf("\t\tConsume %d\n", result);
    out = (out+1) % buffer_size;
    counter--;
  }
  //get nothing
  else {
    printf("\t\tBuffer empty...\n");
  }
  pthread_mutex_unlock(&mutex);
  return result;
}

int Buffer::getCounter() {
  pthread_mutex_lock(&mutex);
  int result = counter;
  pthread_mutex_unlock(&mutex);
  return result;
}

