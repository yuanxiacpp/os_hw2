#include <pthread.h>
#include <synch.h>

class Buffer {
  pthread_mutex_t mutex_p, mutex_r;
};
