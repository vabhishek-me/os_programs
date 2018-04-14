#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define TMAX 5

void* threadFunc(void* arg) {
	for(int i=0; i<8; i++) {
		printf("\nDeteached thread : %lu running", pthread_self());
		sleep(1);
	}
	printf("\nDetached thread completed");
	pthread_exit(NULL);
}

int main(int argc, char** args) {
	pthread_t tid;

	pthread_detach(tid);

	if( pthread_create(&tid, NULL, threadFunc, NULL) ) {
		printf("\nERROR: pthread_create failed\n");
          	exit(-1);
	}

	printf("\nMain Running");
	sleep(5);
	printf("\nMain Running");
	sleep(5);
	printf("\n");
	return 0;
}
