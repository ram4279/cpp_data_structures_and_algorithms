#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int count_bits(long long number)
{
    int count = 0;
    while(number) {
        long long rsb_mask = number & (-number);
        number -= rsb_mask;
        count+=1;
    }
    return count;
}


int main(int argc, char const *argv[])
{
    long long n = (long long)strtoll(argv[1], NULL, 10);
    printf("%lld has %d bits set\n", n, count_bits(n));

    return 0;
}
