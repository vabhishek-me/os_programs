#include <stdio.h>
#include <pthread.h>

#define TMAX 5

pthread_t tids[TMAX];
pthread_mutex_t lock;

void* threadFunc(void* arg) {
  long tid = (long)arg;
  printf("\nThread %ld starting\n", tid);
  printf("\nThread %ld wants to lock mutex\n", tid);

  // lock mutex - if not able to, wait till the mutex is available
  pthread_mutex_lock(&lock); // blocking call

  printf("\nThread %ld acquired mutex lock\n", tid);
  printf("\nThread %ld releasing mutex lock\n", tid);

  pthread_mutex_unlock(&lock); // release lock

  printf("\nThread %ld released mutex lock\n", tid);
  printf("\nThread %ld ending\n", tid);
  pthread_exit(NULL);
}

int main(int argc, char** argv) {

  // initialize mutex lock with default parameters
  pthread_mutex_init(&lock, NULL);

  for(long i=0; i<TMAX; i++)
    pthread_create(&tids[i], NULL, threadFunc, (void *)i);

  printf("\nAll threads created\n");

  for(long i=0; i<TMAX; i++)
    pthread_join(tids[i], NULL);

  printf("\nAll threads joined\n");

  pthread_mutex_destroy(&lock);
  return 0;
}
