#include <stdio.h>
#include <pthread.h>

pthread_t tid1, tid2;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* thread1Func(void* arg) {
  printf("\nThread 1 starting\n");
  printf("\nThread 1 wants to lock mutex\n");

  // lock mutex - if not able to, wait till the mutex is available
  pthread_mutex_lock(&lock); // blocking call
  printf("\nThread 1 acquired mutex lock\n");
  printf("\nThread 1 releasing mutex lock\n");
  pthread_mutex_unlock(&lock); // release lock
  printf("\nThread 1 released mutex lock\n");
  printf("\nThread 1 ending\n");
  pthread_exit(NULL);
}

void* thread2Func(void* arg) {
  printf("\nThread 2 starting\n");
  printf("\nThread 2 wants to lock mutex with trylock\n");

  // try locking mutex - if not able to, move on
  if(!pthread_mutex_trylock(&lock)) { // non-blocking call
    // mutex lock acquired
    printf("\nThread 2 acquired mutex lock\n");
    printf("\nThread 2 releasing mutex lock\n");
    pthread_mutex_unlock(&lock); // release lock
    printf("\nThread 2 released mutex lock\n");
    printf("\nThread 2 ending\n");
    pthread_exit(NULL);
  }

  // non-blocking code
  printf("\nThread 2 didn't get the mutex lock\n");
  printf("\nThread 2 non blocking code\n");
  printf("\nThread 2 ending\n");
  pthread_exit(NULL);
}

int main(int argc, char** argv) {
  pthread_create(&tid1, NULL, thread1Func, NULL);
  pthread_create(&tid2, NULL, thread2Func, NULL);

  printf("\nBoth threads created\n");

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  printf("\nBoth threads joined\n");

  pthread_mutex_destroy(&lock);
  return 0;
}
