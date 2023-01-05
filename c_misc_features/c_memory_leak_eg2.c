#include<stdio.h>
#include<stdlib.h>


int main()
{   
    int a = 12, b = 24;
    
    // inner block of code
    {
        // allocating an integer memory block (4 bytes)
        // scope of sum pointer is till the below left curly brace
        int *sum = (int*)malloc(sizeof(int));
        *sum = a + b;
        
        printf("%d\n", *sum); // prints 36
        
        // this statement should be used to avoid the memory leak
        // free(sum);
        
        // sum = NULL;
    }
    
    return 0;
}
