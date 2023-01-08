#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 10

pthread_mutex_t mutex_lock;
int no_of_mails = 0;


void* routine()
{
    if (pthread_mutex_trylock(&mutex_lock)) {
		printf("Lock success\n");
	} else {
        printf("Lock acquisition failed\n");
    }
	return NULL;
}

int main()
{

	pthread_mutex_init(&mutex_lock, NULL);
	pthread_t threads[MAX_THREADS];

	for (int i = 0; i < MAX_THREADS; i++) {
		pthread_create(&threads[i], NULL, routine, NULL);
	}

	for (int i = 0; i < MAX_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mutex_lock);


}
