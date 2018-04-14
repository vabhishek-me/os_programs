#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define TMAX 5

void* threadFunc(void* arg) {
	long tid = *((long *) arg);
	printf("\nHello from thread %ld\n", tid);
	sleep(1);
	// returning thread id as status
	pthread_exit((void *)tid);
}

int main(int argc, char** args) {
	pthread_t tids[TMAX];
	long thread_data[TMAX];

	// pthread attribute
	pthread_attr_t attr;

	// Initialize and set thread detached attribute
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(long i=0; i<TMAX; i++) {
		thread_data[i] = i;
		printf("\nMain: creating thread %ld\n", i);

		int tstatus = pthread_create(&tids[i], NULL, threadFunc, (void *)&thread_data[i]); // argument passing

		if (tstatus) {
			printf("\nERROR: return code from pthread_create() is %d\n", tstatus);
          		exit(-1);
		}

	}

	// free pthread attribute as the thread attribute is copied by pthread_create
	pthread_attr_destroy(&attr);

	// variable for storing status returned by pthread_join
	void *status;

	for(long i=0; i<TMAX; i++) {
		int tstatus = pthread_join(tids[i], &status);

		if (tstatus) {
			printf("\nERROR: return code from pthread_create() is %d\n", tstatus);
          		exit(-1);
		}
		printf("\nMain: completed join with thread %ld having a status of %ld\n", i, (long)status);
	}

	printf("\nMain: program completed. All threads Joined.\n");
	return 0;
}
