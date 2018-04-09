#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

// bitmap implementation
#define BIT_SIZE 32

long long getBitmapSize(long long size) {
        return ( size/BIT_SIZE + (!!(size%BIT_SIZE)) );
}

void set_bit(uint32_t *bitmap, int index) {
    bitmap[index / BIT_SIZE] |= 1 << (index % BIT_SIZE);
}

void clear_bit(uint32_t *bitmap, int index) {
    bitmap[index / BIT_SIZE] &= ~(1 << (index % BIT_SIZE));
}

int get_bit(uint32_t *bitmap, int index) {
    return 1 & (bitmap[index / BIT_SIZE] >> (index % BIT_SIZE));
}

// pid manager functions
#define MIN 10
#define MAX 1000

uint32_t *pid_map;
pthread_mutex_t lock;

// Creates and initializes a data structure for representing pids; returns —1 if unsuccessfull, 1 if successfull 
int allocate_map(long long size) {
	pid_map = (uint32_t *)calloc(getBitmapSize(size), sizeof(uint32_t));
	if(pid_map == NULL)
		return -1;
	return 1;
}

// Allocates and returns a pid; returns —1 if unable to allocate a pid (all pids are in use)
int allocate_pid() {
	for(int i=MIN; i<MAX; i++) {
		if(get_bit(pid_map, i-1) == 0) {
			set_bit(pid_map, i-1);
			return i;
		}
	}
	return -1; // pid_map full
}

// Releases a pid
void release_pid(int pid) {
	// release pid
	clear_bit(pid_map, pid-1);
}

// process func
void* processFunc(void *arg) {
	int tid = (int *) arg;
	sleep(rand()%10);
	pthread_mutex_lock(&lock);
		int pid = allocate_pid();
		if(pid == -1) {
			printf("\nThread %d : Unable to allocate pid! All PIDs in use.\n", tid);
			pthread_mutex_unlock(&lock);
			pthread_exit(NULL);
		}
	pthread_mutex_unlock(&lock);

	printf("\nThread %d : Allocated PID %d", tid, pid);
	printf("\nThread %d : Running code...", tid);
	sleep(rand()%10+1);
	printf("\nThread %d : Code Completed", tid);

	pthread_mutex_lock(&lock);
		printf("\nThread %d : Releasing allocated PID %d", tid, pid);
		release_pid(pid);	
		printf("\nThread %d : PID %d Released", tid, pid);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

int main(int argc, char** arv) {
	allocate_map(MAX);
	int nThreads;
	printf("\nHow many threads? ");
	scanf("%d", &nThreads);

	pthread_t threads[nThreads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	for(int i=0; i<nThreads; i++)
		pthread_create(&threads[i], &attr, processFunc, (void *)i);

	for(int i=0; i<nThreads; i++)
		pthread_join(threads[i], NULL);

	printf("\nAll threads executed\n");

	return 0;
}
