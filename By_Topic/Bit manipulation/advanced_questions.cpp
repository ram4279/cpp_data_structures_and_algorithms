#include <iostream>
#include <bitset>

using namespace std;

void print_binary(int32_t number)
{
    cout << bitset<32>(number) << endl;
}

/**
 * Given an integer, index and val.
 * Set the val (0|1) at given index in the integer
 */
int32_t set_bit(int32_t number, int index, int val)
{
    int mask;
    if (index > 31) {
        return number;
    }

    if (val) {
        mask = 1 << index;
        number |= mask;
    } else {
        mask = ~(1 << index);
        number &= mask;
    }
    return number;
}


/**
 * Remove right most set bit from a given number
 * The n-1 of a given number will have all bits after the right most set bit
 * will be toggled. so anding n and n-1 will give desired results
 */
#define REMOVE_RSB(x) (x & x-1)

/**
 * Swap bits at two positions
 * 245 - 0b11110101
 *             ↑  ↑
 * Swap pos 0 with pos 4
*/ 
int swap_bits(int num, int i, int j)
{
    int bit_i_val = (num >> i) & 1;
    int bit_j_val = (num >> j) & 1;
    if (bit_i_val != bit_j_val) {
        int mask = (1 << i) | (1 << j);
        num ^= mask;
    }
    return num;
}

/*
 * Find the position of RSB
 */
int get_rsb_position(int number)
{
    int pos = 0;
    int rsb_mask = number & -number;
    while (rsb_mask) {
        pos++;
        rsb_mask >>= 1;
    }
    return pos;
}

/**
 * Check given number is power of 4
 * Approach 1: Naive
 */
bool is_power_of_four(int n)
{
    while (n != 1) {
        if (n % 4 != 0) {
            return false;
        }
        n = n / 4;
    }
    return true;
}

/**
 * Check given number is power of 4
 * Approach 2: Math
 * All power of 4 numbers when divided by 3 will give reminder 1
 * so first check if it is power of 2 and then anding the number with the mask
 * 10101010101010101010101010101010 -> 0xAAAAAAAA
 */
bool is_power_of_four_2(int n)
{
    int power_of_2 = !(n & (n-1));
    return power_of_2 && (n % 3 == 1);
}

/**
 * Check given number is power of 4
 * Approach 3: bit man the power of 4 will have the bit being set at odd postion (0-index)
 * eg 16 - 10000
 * eg 1  - 00001
 * eg 4  - 00100
 */
bool is_power_of_four_3(int n)
{
    int power_of_2 = ((n & (n-1)) == 0);
    return (power_of_2 && ((n & 0xaaaaaaaa) == 0));
}

char to_upper_case(char c)
{
    return (char)(c & '_');
}

char to_lower_case(char c)
{
    return (char)(c | ' ');
}

char invert_case(char c)
{
    return (char)(c ^ ' ');
}


/**
 * Count Number of bits to be flipped to #convert A to B:
 * A = 32; 100101
 * B = 20; 010100
 * ---------------
 * xor AB: 110001
 * 
 * Count the xor bits thats it
*/
int count_bits_to_flipped(int x, int y)
{
    int xor_res = x ^ y;
    int res = 0;
    while (xor_res)
    {
        xor_res &= (xor_res-1);
        res++;
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int32_t number = 31;
    print_binary(number);
    cout << "Setting 0th bit to 0" << endl;
    number = set_bit(number, 0, 0);
    print_binary(number);
    cout << "Setting 31st bit to 1" << endl;
    number = set_bit(number, 31, 1);
    print_binary(number);

    number = 63;
    print_binary(number);
    number = REMOVE_RSB(number);
    printf("after removing RSB\n");
    print_binary(number);

    number = 64;
    print_binary(number);
    int pos = get_rsb_position(number);
    printf("Position of rsb = %d\n", pos);
    
    number = 1;
    if (is_power_of_four_3(number)) {
        cout << number << "is power of 4" << endl;
    } else {
        cout << number << "is not power of 4" << endl;
    }

    cout << "Upper case of c is " << to_upper_case('c') << endl;

    int A = 32, B = 20;
    cout << "Number to flipped to get from 20 to 32 " << count_bits_to_flipped(A,B) << endl; 

    return 0;
}
