#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int N = 5;
    int *ptr = mmap(NULL, N * sizeof(int), PROT_READ|PROT_WRITE,
                    MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);

    if (ptr == MAP_FAILED)
    {
        perror("MMap creation failed\n");
        return -1;
    }
    

    for (size_t i = 0; i < N; i++)
    {
        *(ptr + i) = i+1;
    }
    
    for (size_t i = 0; i < N; i++)
    {
        printf("%d\n", *(ptr + i));
    }
    

    int err = munmap(ptr, N * sizeof(int));

    if (err) {
        perror("munmap failed\n");
    }
    return 0;
}