#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* routine() {
	printf("Routine called from threads\n");
}


int main(int argc, char** argv)
{
	pthread_t t1;
	if (pthread_create(&t1, NULL, routine, NULL) != 0) {
		return 1;
	}

    // Only uncommenting below line you can see output else main will run and complete first
	//sleep(3);
	return 0;
}
