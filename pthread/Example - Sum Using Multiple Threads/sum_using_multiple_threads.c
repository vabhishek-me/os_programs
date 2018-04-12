#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long sum;
void* sumFunc(void *);

typedef struct sumFunc_thread_data {
	pthread_t thread;
	long long limit;
	long long lsum;
} SUM_THREAD;

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("\n Usage: %s <num 1> <num 2> .... <num n>\n\n", argv[0]);
		exit(-1);
	}

	int nums = argc - 1;

	SUM_THREAD *sumThreads = (SUM_THREAD *)malloc(nums * sizeof(*sumThreads));
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for(int i=0; i < nums; i++) {
		sumThreads[i].limit = atoll(argv[i+1]);
		pthread_create(&sumThreads[i].thread, &attr, sumFunc, (void *)&sumThreads[i]);
	}

	for(int i=0; i < nums; i++) {
		pthread_join(sumThreads[i].thread, NULL);
		printf("The sum upto %lld is %lld\n", sumThreads[i].limit, sumThreads[i].lsum);
	}
}

void* sumFunc(void* arg) {
	SUM_THREAD* data = (SUM_THREAD *) arg;

	sum = 0;
	for(long long i=1; i<=data->limit; i++)
		sum += i;
	data->lsum = sum;	
	pthread_exit(NULL);
}
