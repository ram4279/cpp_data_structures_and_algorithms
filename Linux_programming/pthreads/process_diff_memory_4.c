#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int gvar = 1;

int main()
{
	
	pid_t pid;
	pid = fork();
	if (pid == -1) {
		printf("fork failed");
		return 1;
	}

	if (pid == 0) {
		gvar++;
		printf("value of gvar = %d\n", gvar);
		printf("Address of gvar = %p\n", &gvar);
	}


	if (pid != 0) {
		sleep(1);
		printf("value of gvar = %d\n", gvar);
		printf("Address of gvar = %p\n", &gvar);
		wait(NULL);
	}

	return 0;
}
