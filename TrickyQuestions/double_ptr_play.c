#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char** ptr = malloc(128);
    printf("%p\n", ptr);
    ptr++;
    printf("%p\n", ptr);
    //free(ptr);
    return 0;
}
