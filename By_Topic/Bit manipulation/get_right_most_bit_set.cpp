#include <iostream>
#include <stdint.h>
#include <bitset>
using namespace std;

#define M 32

/*
Assume there are X no of 1's and 0's before the rightmost set bet and after it some 0
So for a given number if we negate it the X no of 1's and 0's get flipped, the rsb 1 will become 0, and all 0's after the rsb will become 1
Now if we add 1 to the previous step all the 1's after the rsb will become 0 and and the rsb will become 1.
If we now & the result from previos step with the given number we will get the mask of the RSB

The last three steps are nothing but to get the 2's complement of the given number.

Two ways to get twos complement of the given number.
1. (~number) + 1
2. -number

*/
int main(int argc, char const *argv[])
{
    uint32_t number = 324;
    uint32_t mask_rsb = number & -number;
    uint32_t mask_rsb2 = number & ((~number) + 1);
    bitset<M> number_set(number);
    bitset<M> rsb_mask_bitset(mask_rsb);
    cout << "RSB (Right most set) mask of " << number_set 
        << "\nis\n" << rsb_mask_bitset 
        << "\nand\n" << bitset<M>(mask_rsb2) << endl;

    return 0;
}
