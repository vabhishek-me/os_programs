#include <stdio.h>
#include <pthread.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("\nUsage: %s <num 1> <num 2> .... <num n>\n\n", argv[0]);
	}
}
