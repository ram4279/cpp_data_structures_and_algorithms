/**
 * Car should run when fuel is more than 40
 * else it should keep on waiting
 * Fueling will done increments in 10s
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int fuel_gvar = 0;

pthread_mutex_t mutex_fuel;
pthread_cond_t cond_fuel;

void* fuel_handler()
{
    printf("%s called\n", __func__);
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex_fuel);
        fuel_gvar += 10;
        printf("Fuel is now = %d\n", fuel_gvar);
        pthread_mutex_unlock(&mutex_fuel);
        pthread_cond_signal(&cond_fuel);
        sleep(1);
    }
}

void* car_handler()
{
    printf("%s called\n", __func__);
    pthread_mutex_lock(&mutex_fuel);
    while (fuel_gvar < 50) {
        printf("Car is not moving\n");
        pthread_cond_wait(&cond_fuel, &mutex_fuel);
    }
    printf("Car moved\n");
    fuel_gvar -= 50;
    printf("Car is moving with fuel: %d\n", fuel_gvar);
    pthread_mutex_unlock(&mutex_fuel);
}

int main(int argc, char const *argv[])
{
    pthread_t fuel, car;
    int ret = 0;
    pthread_mutex_init(&mutex_fuel, NULL);
    pthread_cond_init(&cond_fuel, NULL);
    ret = pthread_create(&car, NULL, car_handler, NULL);
    if (ret) {
        perror("pthread_create failed for car");
        exit(1);
    }

    ret = pthread_create(&fuel, NULL, fuel_handler, NULL);
    if (ret) {
        perror("pthread_create failed for fuel");
        exit(1);
    }

    ret = pthread_join(fuel, NULL);
    if (ret) {
        perror("pthread_join failed for car\n");
        exit(1);
    }
    
    ret = pthread_join(car, NULL);
    if (ret) {
        perror("pthread_join failed for car\n");
        exit(1);
    }

    pthread_mutex_destroy(&mutex_fuel);
    pthread_cond_destroy(&cond_fuel);
    return 0;
}
