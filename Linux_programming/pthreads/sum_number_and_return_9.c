#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 2
#define MAX_ARR_SIZE 10

int arr[MAX_ARR_SIZE] = {1,2,3,4,5,6,7,8,9,10};

void* summer(void* arg)
{
    int index = *(int *)arg;
    int sum   = 0;
    for (int i = 0; i < MAX_ARR_SIZE/2; i++) {
        sum += arr[index + i];
    }
    *(int*)arg = sum;
    return arg;
}

int main(int argc, char const *argv[])
{
    int res = 0;
    pthread_t tds[MAX_THREADS];
    
    int gsum = 0;
    for (int i = 0; i < 2; i++) {
        int *arg = malloc(sizeof(int));
        *arg = i * (MAX_ARR_SIZE / 2);
        res = pthread_create(&tds[i], NULL, summer, arg);
        if (res != 0) {
            perror("pthread_create failed\n");
            exit(1);
        }
    }

    for (int i = 0; i < 2; i++) {
        int *r;
        res = pthread_join(tds[i], (void**)&r);
        if (res) {
            perror("pthread_join failed\n");
            exit(1);
        }
        gsum += *r;
        free(r);
    }

    printf("Sum of the elements of array = %d\n", gsum);
    return 0;
}
