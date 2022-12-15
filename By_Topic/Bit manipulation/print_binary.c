#include <stdio.h>
#include <stdlib.h>

void print_binary(long long n) {
  // use a bitmask to extract the rightmost bit
  unsigned long long mask = 1ull << 63;

  // check if the number is negative
  if (n < 0) {
    // negate the number
    n = -n;

    // print the sign bit (1 for negative numbers)
    printf("1");
  } else {
    // print the sign bit (0 for positive numbers)
    printf("0");
  }

  // loop over all 63 bits (ignoring the sign bit)
  for (int i = 0; i < 63; i++) {
    // print the rightmost bit
    printf("%lld", (n & mask) == 0 ? 0 : 1);

    // shift the bitmask one bit to the right
    mask >>= 1;
  }
}

int main(int argc, char** argv) {
  // check if a number was provided as a command-line argument
  if (argc < 2) {
    printf("Usage: please provide an integer as an argument\n");
    return 1;
  }

  // convert the argument to a long long
  long long n = (long long)strtoll(argv[1], NULL, 10);

  printf("Binary representation of %lld: ", n);
  print_binary(n);
  printf("\n");

  return 0;
}
