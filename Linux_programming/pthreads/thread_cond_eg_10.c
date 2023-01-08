#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 5

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

int wait = 0;

void* routine()
{
    printf("rountine started\n");
    pthread_mutex_lock(&mutex_lock);
    wait++;
    sleep(1);
    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&mutex_lock);
    printf("rountine finished\n");
}

int main()
{
    printf("Main thread started\n");
    pthread_t tds[MAX_THREADS];
    for (int  i = 0; i < MAX_THREADS; i++) {
        pthread_create(&tds[i], NULL, routine, NULL);
    }

    while (wait < MAX_THREADS)
    {   
        pthread_cond_wait(&cond_var, &mutex_lock);
        printf("thread finished wait = %d\n", wait);
    }
    
    printf("Main thread finished\n");

}