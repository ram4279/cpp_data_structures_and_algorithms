#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *ptr = (int*) malloc(10);

	
    /* By calling realloc with size 0 the memory occupied by the ptr will be freed */
	realloc(ptr, 0);
	

	return 0;
}
