#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define TMAX 5

pthread_t tids[TMAX];
long thread_data[TMAX];

void* threadFunc(void* arg) {
	long tid = *((long *) arg);
	printf("\nHello from thread %ld\n", tid);
	sleep(tid);
	if(pthread_equal(tids[0], pthread_self())) { // if the calling thread is 0
		pthread_cancel(tids[4]); // cancelling thread 4
		printf("\nCancelling thread 4\n");
	}
	printf("\nBye from thread %ld\n", tid);
	// returning thread id as status
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
