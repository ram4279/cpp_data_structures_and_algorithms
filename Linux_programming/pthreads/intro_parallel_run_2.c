#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void* routine() {
	printf("Routine called from threads\n");
	sleep(3);
	printf("Routine ended from threads\n");
}


int main(int argc, char** argv)
{
	pthread_t t1;
	pthread_t t2;
	if (pthread_create(&t1, NULL, routine, NULL) != 0) {
		return 1;
	}

	if (pthread_create(&t2, NULL, routine, NULL) != 0) {
		return 1;
	}
	
	if (pthread_join(t1, NULL)) {
		return 1;
	}
	
	if (pthread_join(t2, NULL)) {
		return 1;
	}
	return 0;
}
