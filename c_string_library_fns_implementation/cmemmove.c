#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *cmemmove(void *dst, const void *src, size_t size)
{
    char *d_ptr = (char *)dst;
    char *s_ptr = (char *)src;

    char *temp_arr = malloc(sizeof(size));
    for (size_t i = 0; i < size; i++) {
        temp_arr[i] = s_ptr[i];
    }

    for (size_t i = 0; i < size; i++) {
        d_ptr[i] = temp_arr[i];
    }
    free(temp_arr);
    return dst;
}

/**
 * s   d           ls   ds
 * 1 2 3 4 5 6 7 8 9  X X X
 *     d 
 * 1 2 1 2 3 4 5 6 7 8 9
 * 
 */
void *dmemmove(void *dest, const void *src, size_t len)
{
    char *d = dest;
    const char *s = src;
    if (d < s)
        while (len--)
            *d++ = *s++;
    else {
        char *lasts = s + (len - 1);
        char *lastd = d + (len - 1);
        while (len--)
            *lastd-- = *lasts--;
    }
    return dest;
}

int main(int argc, char const *argv[])
{
    char *src_str = "sairamkamlay";
    char dst_str[20] = {'\0'};
    char *dst_ptr = (char *)cmemmove(dst_str, src_str, strlen(src_str) + 1);

    printf("size of src_str = %llu\n", strlen(src_str));
    printf("dst_ptr = %s\n", dst_ptr);
    printf("dst_str = %s\n", dst_str);

    return 0;
}
