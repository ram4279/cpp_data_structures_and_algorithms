#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 4

void* roll_dice()
{
	int *result = malloc(sizeof(int));
	*result = rand() % 6 + 1;
//	printf("address of res inside %s is %p\n", __func__, result);
	return (void *) result;
}

int main()
{
	srand(time(NULL));
	pthread_t threads[MAX_THREADS];

	int* res;

	for (int i = 0; i < MAX_THREADS; i++) {
		if (pthread_create(&threads[i], NULL, roll_dice, NULL)) {
			fprintf(stderr, "Thread creation failed\n");
		}
	}


	for (int i = 0; i < MAX_THREADS; i++) {
		if (pthread_join(threads[i], (void**)&res)) {
			fprintf(stderr, "Thread join failed\n");
		}
		printf("Dice %d results %d\n", i, *res);
//		printf("address of res inside %s is %p\n", __func__, res);
	}

	free(res);
	return 0;
}

/*
 * Remember the res and result point to same location thats why we are able to
 * free the result variable allocated in roll_dice function from main function
 * using free(res) call
 */
