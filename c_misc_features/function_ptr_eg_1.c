#include <stdio.h>
#include <stdlib.h>

int sum_int(int a, int b)
{
    printf("%d\n", a + b);
    return a + b;
}


int main()
{
    /* Lets declare function pointer */
    /* The below one is function ptr that can hold address of function with
     * return type int and that takes two int arguments */
    int (*funptr) (int, int);

    /* Now assign sum_int to our function ptr */
    funptr = sum_int;
    
    funptr(10,10);
    
    return 0;
}

