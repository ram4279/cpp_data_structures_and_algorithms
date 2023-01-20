#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    long long* lptr = calloc(1, sizeof(long long));
    // memset(lptr, 0, sizeof(lptr));
    (*lptr)+=100000;
    printf("%lld", *lptr);
    return 0;
}
