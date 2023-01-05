#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 4

pthread_mutex_t mutex_lock;
int no_of_mails = 0;


void* routine()
{
	for (int i = 0; i < 10000000; i++) {
		pthread_mutex_lock(&mutex_lock);
		no_of_mails++;
		pthread_mutex_unlock(&mutex_lock);
	}
	return NULL;
}

int main()
{

	pthread_mutex_init(&mutex_lock, NULL);
	pthread_t threads[MAX_THREADS];

	for (int i = 0; i < MAX_THREADS; i++) {
		printf("Thread %d started\n", i);
		pthread_create(&threads[i], NULL, routine, NULL);
	}

	for (int i = 0; i < MAX_THREADS; i++) {
		pthread_join(threads[i], NULL);
		printf("Thread %d ended\n", i);
	}

	printf("Total no of mails received = %d\n", no_of_mails);
	pthread_mutex_destroy(&mutex_lock);


}
