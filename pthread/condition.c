#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define TMAX 5

pthread_t tids[TMAX];
pthread_mutex_t lock;

// condition variable
pthread_cond_t condition;

long pattern[TMAX] = {2, 1, 4, 0, 3}; // threading running sequence
int threadN = 0;

void* threadFunc(void* arg) {
  long tid = (long)arg;
  printf("\nThread %ld wants to run\n", tid);

  // locking mutex
  pthread_mutex_lock(&lock);

  while(tid != pattern[threadN]) {
    printf("\nThread %ld - waiting for its turn\n", tid);
    // waiting for condition
    pthread_cond_wait(&condition, &lock);
  }

  printf("\nThread %ld running\n", tid);
  sleep(rand()%5+1);
  printf("\nThread %ld done running\n", tid);

  // set condition for next thread
  ++threadN;
  printf("\nThread %ld modified the condition\n", tid);

  // broadcase condition signal
  pthread_cond_broadcast(&condition);

  printf("\nThread %ld releasing mutex lock\n", tid);

  // release mutex lock
  pthread_mutex_unlock(&lock);

  printf("\nThread %ld ending\n", tid);
  pthread_exit(NULL);
}

int main(int argc, char** argv) {

  printf("\nThreads should run in this sequence : {");
  for(int i=0; i<TMAX; i++) printf(" %ld ", pattern[i]);
  printf("}\n");

  pthread_mutex_init(&lock, NULL);
  
  // condition variable initialized
  pthread_cond_init(&condition, NULL);

  for(long i=0; i<TMAX; i++)
    pthread_create(&tids[i], NULL, threadFunc, (void *)i);

  printf("\nAll threads created\n");

  for(long i=0; i<TMAX; i++)
    pthread_join(tids[i], NULL);

  printf("\nAll threads joined\n");
  pthread_mutex_destroy(&lock);
  return 0;
}
