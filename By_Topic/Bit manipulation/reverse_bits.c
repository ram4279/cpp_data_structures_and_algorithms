/*
Given a 32 bit number X, reverse its binary form and print the answer in decimal.
Input:
X = 1
Output:
2147483648
Explanation:
Binary of 1 in 32 bits representation-
00000000000000000000000000000001
Reversing the binary form we get,
10000000000000000000000000000000,
whose decimal value is 2147483648.
*/

#include <stdio.h>

long long reversedBits(long long x)
{
    long long result = 0;
    for (int i = 0; i < 32; i++) {
        // get the i-th bit of x and shift it to the correct position in the result
        result |= ((x >> i) & 1) << (31 - i);
    }
    return result;
}
int main(int argc, char const *argv[])
{
    long long n = 1;
    long long res = reversedBits(n);
    printf("%lld\n", res);

    return 0;
}
