#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
	printf("My PID is %d\n", (int) getpid());
	printf("forking....\n\n");

	pid_t pid = fork();

	if(pid < 0) { // fork failed
		printf("Fork failed! \n");
		exit(-1);
	}

	if(pid == 0) { // child process
		printf("\n--> Starting Child Process \n");
		printf("Hello! I'm the child process with process id %d\n", (int)getpid());
		printf("Sleeping for 5 secs\n");
		sleep(5);
		printf("--> Ending Child Process \n\n");
		exit(0); // end child process
	}

	//parent process continues
	printf("Parent process with process id %d\n", (int)getpid());
	printf("Waiting for the child process to finish\n");
	wait(NULL);
	printf("Parent Exiting...\n");
	
	return 0;
}
