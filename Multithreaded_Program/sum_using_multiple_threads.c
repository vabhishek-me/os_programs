#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long sum;
void* sumFunc(void *);

struct sumFunc_struct {
	long long limit;
	long long lsum;
};

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("\n Usage: %s <num 1> <num 2> .... <num n>\n\n", argv[0]);
		exit(-1);
	}

	int nums = argc - 1;

	struct sumFunc_struct toSum[nums];
	pthread_t sumThreads[nums];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for(int i=0; i < nums; i++) {
		toSum[i].limit = atoll(argv[i+1]);
		pthread_create(&sumThreads[i], &attr, sumFunc, &toSum[i]);
	}

	for(int i=0; i < nums; i++) {
		pthread_join(sumThreads[i], NULL);
		printf("The sum upto %lld is %lld\n", toSum[i].limit, toSum[i].lsum);
	}
}

void* sumFunc(void* arg) {
	struct sumFunc_struct* data = (struct sumFunc_struct*) arg;

	sum = 0;
	for(long long i=1; i<=data->limit; i++)
		sum += i;
	data->lsum = sum;	
	pthread_exit(0);
}
