#include <stdio.h>
#include <stdlib.h>

int sum_int(int a, int b)
{
    printf("%d\n", a + b);
    return a + b;
}


int main()
{
    /* Using type def we can create our own funtion pointer variables*/
    typedef int (*funptr) (int, int);

    /* Lets declare function pointer */
    /* The below one is function ptr that can hold address of function with
     * return type int and that takes two int arguments */
    funptr sumptr;

    /* Now assign sum_int to our function ptr */
    sumptr = sum_int;
    
    sumptr(10,10);
    
    return 0;
}

