#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int no_of_mails = 0;

pthread_mutex_t mutex;

void* increment_mail()
{
	// mail received
	// increment mail count
	for (int i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex);
		no_of_mails++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}


int main()
{
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, increment_mail, NULL);
	pthread_create(&t2, NULL, increment_mail, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("No of mails received = %d\n", no_of_mails);
	pthread_mutex_destroy(&mutex);
	return 0;

}
