#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    time_t current_time;
    time(&current_time);

    printf("Current time is %s", ctime(&current_time));
    
    time_t *curent_time = malloc(sizeof(time_t));
    time(curent_time);

    printf("Current time is %s", ctime(curent_time));
    return 0;
}
