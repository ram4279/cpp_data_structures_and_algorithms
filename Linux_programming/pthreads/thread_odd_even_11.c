#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREAD 2
#define MAX_LIMIT 20

pthread_mutex_t mutex_lock;
pthread_cond_t switch_cond;
int idx = 0;

void* odd_printer(void *arg)
{
    while (idx < MAX_LIMIT) {
        pthread_mutex_lock(&mutex_lock);
        while (idx % 2 == 0) {
            pthread_cond_wait(&switch_cond, &mutex_lock);
        }
        printf("%s printed: %d\n", __func__, idx);
        idx++;
        pthread_mutex_unlock(&mutex_lock);
        pthread_cond_signal(&switch_cond);
    }
}

void* even_printer(void *arg)
{
    while (idx < MAX_LIMIT) {
        pthread_mutex_lock(&mutex_lock);
        while (idx % 2 != 0) {
            pthread_cond_wait(&switch_cond, &mutex_lock);
        }
        printf("%s printed: %d\n", __func__, idx);
        idx++;
        pthread_mutex_unlock(&mutex_lock);
        pthread_cond_signal(&switch_cond);
    }
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex_lock, NULL);
    pthread_cond_init(&switch_cond, NULL);
    pthread_t tds[MAX_THREAD];
    for (int i = 0; i < MAX_THREAD; i++) {
        if (i == 0) {
            pthread_create(&tds[i], NULL, odd_printer, NULL);
        } else {
            pthread_create(&tds[i], NULL, even_printer, NULL);
        }
    }
    
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(tds[i], NULL);
    }

    pthread_mutex_destroy(&mutex_lock);
    pthread_cond_destroy(&switch_cond);
    return 0;
}
