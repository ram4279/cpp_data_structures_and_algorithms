#include <iostream>
#include <bitset>

using namespace std;

void swap_bits(unsigned int* x, int p, int q) {
  // check if the bits at positions p and q are different
  if (((*x >> p) & 1) != ((*x >> q) & 1)) {
    // flip the bits at positions p and q by XORing them with 1
    *x ^= (1 << p) | (1 << q);
  }
}


int main(int argc, char const *argv[])
{
    unsigned int x = 10;
    cout << bitset<8>(x) << endl;
    swap_bits(&x, 0, 3);
    cout << bitset<8>(x) << endl;
    return 0;
}
