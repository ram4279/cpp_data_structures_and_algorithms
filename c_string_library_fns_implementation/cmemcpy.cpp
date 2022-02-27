#include <cstdio>
#include <cstdlib>

void* cmemcpy(void* dest, const void* src, size_t bytes)
{
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    char* dstptr = (char*)dest;
    char* srcptr = (char*)src;

    for (size_t i = 0; i < bytes; i++) {
        dstptr[i] = srcptr[i];
    }
    return dest;
}

int main()
{
    char str1[] = "Geeks"; 
    char str2[] = "Quiz"; 
       
    puts("str1 before memcpy ");
    puts(str1);
    
    cmemcpy(str1, str2, sizeof(str2));

    puts("\nstr1 after memcpy ");
    puts(str1);

    return 0;
    
}
