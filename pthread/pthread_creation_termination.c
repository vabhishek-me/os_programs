#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define TMAX 5

void* threadFunc(void* arg) {
	long tid = (long) arg;
	printf("\nHello from thread %ld\n", tid);
	sleep(1);
	pthread_exit(NULL);
}

int main(int argc, char** args) {

	// thread variable
	pthread_t tids[TMAX];

	for(long i=0; i<TMAX; i++) {

		// create thread
		int tstatus = pthread_create(&tids[i], NULL, threadFunc, (void *)i); // passing value of i as void pointer value - dont! pass address as it will be changed and shared

		if (tstatus) { // thread creation failed
			printf("\nERROR: return code from pthread_create() is %d\n", tstatus);
          		exit(-1);
		}

	}

	/*
	 * By having main() explicitly call pthread_exit() as the last thing it does,
	 * main() will block and be kept alive to support the threads it created until they are done.
	 */
	pthread_exit(NULL);
}
