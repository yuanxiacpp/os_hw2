#include <pthread.h>
#include <stdlib.h>
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
  if (counter != buffer_size) {
    content[in] = val;
    in = (in + 1) % buffer_size;
    counter++;
    status = 0;
  }
  //put nothing
  else {

  }
  pthread_mutex_unlock(&mutex);
  return status;
}

int Buffer::get() {
  pthread_mutex_lock(&mutex);
  int result = -1;
  if (counter != 0) {
    result = content[out];
    out = (out+1) % buffer_size;
    counter--;
  }
  //get nothing
  else {

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

