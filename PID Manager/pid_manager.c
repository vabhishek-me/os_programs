#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MIN 10
#define MAX 1000

// Creates and initializes a data structure for representing pids; returns —1 if unsuccessfull, 1 if successfull 
int allocate_map();

// Allocates and returns a pid; returns —1 if unable to allocate a pid (all pids are in use)
int allocate_pid();

// Releases a pid
void release_pid(int pid);


// process func
void* processFunc(void *arg) {
	printf("\nExecuting thread...");
	pthread_exit(NULL);
}

int main(int argc, char** arv) {
	int nThreads;

	printf("\nHow many threads? ");
	scanf("%d", &nThreads);

	pthread_t threads[nThreads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	for(int i=0; i<nThreads; i++)
		pthread_create(&threads[i], &attr, processFunc, NULL);

	for(int i=0; i<nThreads; i++)
		pthread_join(threads[i], NULL);

	printf("\nAll threads executed\n");

	return 0;
}
