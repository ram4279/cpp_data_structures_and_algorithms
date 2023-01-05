#include <iostream>
#include <cstdint>
#include <bitset>

using namespace std;

#define MAXBITS 32

/*
 * eg shift by 4
 * 11110000000000000000000111111111
 * dropped part = 00000000000000000000000000001111
 * second half  = 00000000000000000001111111110000
 * OR           = 00000000000000000001111111111111
 */
uint32_t left_rotate(uint32_t number, uint32_t bits)
{
    uint32_t dropped_part = number >> (MAXBITS - bits);
    uint32_t second_half = number << bits;
    return second_half | dropped_part;
}
/*
 * eg shift by 3
 * 00000000000000000000000111111111
 * dropped_part = 111
 * after dropping = 00000000000000000000000000111111
 * or both (11100000000000000000000000000000 | 00000000000000000000000000111111)
 */
uint32_t right_rotate(uint32_t number, uint32_t bits)
{
    uint32_t dropped_part = number << (MAXBITS - bits);
    uint32_t after_drop_part = number >> bits;
    return after_drop_part | dropped_part;
}

int main(int argc, char const *argv[])
{
    uint32_t number;
    scanf("%d", &number);
    cout << bitset<32> (number) << endl;
    number = left_rotate(number, 3);
    cout << bitset<32> (number) << endl;
    number = right_rotate(number, 3);
    cout << bitset<32> (number) << endl;
    return 0;
}
