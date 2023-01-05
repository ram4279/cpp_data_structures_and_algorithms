#include <iostream>
#include <stdint.h>
#include <bitset>
using namespace std;

int8_t swap_nibble(int8_t number)
{
    return (number << 4) | (number >> 4);
}


int main(int argc, char const *argv[])
{
    int8_t x = 7;
    cout << bitset<8>(x) << endl;
    x = swap_nibble(7);
    cout << bitset<8>(x) << endl;
    return 0;
}
