#include <stdio.h>

int main(int argc, char const *argv[])
{
    int x = 11;
    int y = 11;

    printf("x = %d, y = %d", x , y);
    
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;

    /**
     * How this works
     * step 1 x = x ^ y;
     * 
     * in step 2 substitute x with x ^ y
     * y = (x ^ y) ^ y 
     * which becomes
     * y = x because y ^ y is 0 and x ^ 0 is x
     * now y becomes x
     * 
     * Now in step again substitue x with x ^ y cause it is still not changed
     * x = (x ^ y) ^ y
     * oh oh now y has become x in previous step so sub only the second y with x as the first y is not separate y it was expanded from step 1
     * x = (x ^ y) ^ x
     * x = y <- x became y
     * 
     * 
     */

    printf("x = %d, y = %d", x , y);
    return 0;
}
