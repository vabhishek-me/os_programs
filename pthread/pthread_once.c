#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define TMAX 5

pthread_t tids[TMAX];

// pthread once control variable
pthread_once_t once_control = PTHREAD_ONCE_INIT;

long thread_data[TMAX];
int value = 5;

void initializeGlobals() {
	printf("\ninitializing globals\n");
	value++;
}

void* threadFunc(void* arg) {
	long tid = *((long *) arg);
	printf("\nThread %ld entered\n", tid);

	// pthread once called
	if(pthread_once(&once_control, initializeGlobals)) {
		printf("pthread_once failed, thread %ld, errno=%d\n", tid, errno);
	}

	printf("\nThread %ld -> value = %d\n", tid, value);
	printf("\nThread %ld exiting\n", tid);
	pthread_exit((void *)tid);
}

int main(int argc, char** args) {
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for(long i=0; i<TMAX; i++) {
		thread_data[i] = i;
		if( pthread_create(&tids[i], NULL, threadFunc, (void *)&thread_data[i]) ) {
			printf("\nERROR: pthread_create failed\n");
          		exit(-1);
		}
	}
	pthread_attr_destroy(&attr);

	for(long i=0; i<TMAX; i++) {
		if( pthread_join(tids[i], NULL) ) {
			printf("\nERROR: pthread_create failed\n");
          		exit(-1);
		}
	}
	return 0;
}
