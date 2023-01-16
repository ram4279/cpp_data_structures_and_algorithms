#include <stdio.h>
#include <stdlib.h>

// Some good links
// https://publications.gbdirect.co.uk//c_book/chapter8/const_and_volatile.html


/**
 * A volatile object is one whose value might change spontaneously. 
 * That is, when you declare an object to be volatile, 
 * you're telling the compiler that the object might change state even 
 * though no statements in the program appear to change it.
 */

volatile int a = 10;

int main(int argc, char const *argv[])
{
    if (a == 10) {
        printf("a is 10\n");
    } 
    /**
     * This else case can be part of optimisation done by compiler and
     * the comipler will remove it
    */
    else {
        printf("a is not 10\n");
    }
    return 0;
}
