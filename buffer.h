#include <pthread.h>
#include <semaphore.h>

class Buffer {
 private:
  sem_t mutex;
  //pthread_mutex_t mutex;
  int in;
  int out;
  int counter;
  int buffer_size;
  int *content;
 public:
  Buffer(int size);
  //produce a randomly generated value and store and return it
  int put(int val);
  //return the val that was consumed


  int get();

  int getSize() {
    return buffer_size;
  }
  int getCounter();
};
