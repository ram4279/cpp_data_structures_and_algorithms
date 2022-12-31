#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREAD 10

int primes[10] = {2,3,5,7,11,13,17,19,23,29};


void* routine(void* arg)
{
	int index = *(int *)arg;
	printf("At index %d = %d\n", index, primes[index]);
	free(arg);
}

int main()
{

	pthread_t threads[MAX_THREAD];
	for (int i = 0; i < MAX_THREAD; i++) {
		int *a = malloc(sizeof(int));
		*a = i;
		pthread_create(&threads[i], NULL, &routine, a);
	}

	for (int i = 0; i < MAX_THREAD; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("\n");
	return 0;
}
