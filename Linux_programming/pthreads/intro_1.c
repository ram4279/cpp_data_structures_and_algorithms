#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* routine() {
	printf("Routine called from threads\n");
}


int main(int argc, char** argv)
{
	pthread_t t1;
	if (pthread_create(&t1, NULL, routine, NULL) != 0) {
		return 1;
	}

	if (pthread_join(t1, NULL)) {
		return 1;
	}
	return 0;
}
