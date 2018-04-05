#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* fibo(void *);

int main(int argc, char** argv) {
	if(argc < 2) {
		printf(" Usage: %s <num> \n", argv[0]);
	}

	long long* num = malloc(sizeof(*num));
	long long* ans;
	*num = atoll(argv[1]);

	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid, &attr, fibo, num);

	pthread_join(tid, (void **) &ans);
	printf("The fibonacci of %lld = %lld \n", *num, *ans);
}

void* fibo(void *arg) {
	long long* num = (long long*) arg;

	// fibonacci logic
	long long a = 0,
	     	  b = 1,
		  c = 0;
	for(long long i=1; i<*num; i++) {
		c = a+b;
		a = b;
		b = c;
	}

	long long* ans = malloc(sizeof(*ans));
	*ans = b;
	pthread_exit(ans);
}
