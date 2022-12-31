#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int gvar = 1;

void* t1()
{
	printf("Inside %s\n", __func__);
	gvar++;
	printf("gvar = %d\n", gvar);
}

void* t2()
{
	printf("gvar = %d\n", gvar);
}


int main()
{
	pthread_t pt1, pt2;
	pthread_create(&pt1, NULL, t1, NULL);
	pthread_join(pt1, NULL);
	pthread_create(&pt2, NULL, t2, NULL);
	pthread_join(pt2, NULL);
	return 0;
}
