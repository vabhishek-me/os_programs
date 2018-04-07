#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
	printf("\nMy PID is %d\n", (int) getpid());
	printf("\nforking....\n");

	pid_t pid = fork();
	printf("\nFork returned : %d", (int) pid);
	
	if(pid < 0) { // fork failed
		printf("\n Fork failed! \n");
		exit(-1);
	}

	if(pid == 0) { // child process
		printf("\n----- Begin Child -----");
		printf("\nHello! I'm the child process with process id %d", (int)getpid());
		printf("\n----- End Child -----\n");
	} else { // parent process
		printf("\n----- Begin Parent -----");
		printf("\nHey! I'm the parent process with process id %d", (int)getpid());
		printf("\n----- End Parent -----\n");
	}
	return 0;
}
