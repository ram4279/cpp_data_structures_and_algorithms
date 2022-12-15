#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


/*
 * Generic comment
 * k starts from 0 here.
 * if user wants k to start from 1 instead the use k - 1 
 */
void print_binary(int32_t number)
{
    for (int i = 31; i >= 0; i--) {
        if ((1 << i) & number) {
            printf("%d", 1);
        } else {
            printf("%d", 0);
        }
    }
    printf("\n");
    return;
}

/*
 * 64           - 1000000
 * 0th bit mask - 0000001 (&)
 * ----------------------
 * res          - 0000000
 * ----------------------
 */
static inline bool is_kth_bit_set(int32_t number, int32_t k)
{
    int32_t mask = (1 << k);
    return number & mask;
}

/*
 * 64           - 1000000
 * 0th bit mask - 0000001 (|)
 * ----------------------
 * res          - 1000001
 * ----------------------
 */
static inline int32_t set_kth_bit(int32_t number, int32_t k)
{
    int32_t mask = (1 << k);
    return number | mask;
}

/*
 * 64           - 1000000
 * 2th bit mask - 0000100
 * ----------------------
 * res          - 1000100
 * ----------------------
 */
static inline int32_t toggle_kth_bit(int32_t number, int32_t k)
{
    int32_t mask = (1 << k);
    return number ^ mask;
}

/*
 * 66           - 1000010
 * 1st bit mask - 1111101 (&) 
 * ----------------------
 * res          - 1000000
 * ----------------------
 */
static inline int32_t unset_kth_bit(int32_t number, int32_t k)
{
    int32_t mask = ~(1 << k);
    return number & mask;
}

int main(int argc, char const *argv[])
{
    int32_t given_number = atoi(argv[1]);
    print_binary(given_number);
    printf(" 2nd bit is %s set for %d\n", 
        (is_kth_bit_set(given_number, 2) == true ? "" : "not"), given_number);
    given_number = set_kth_bit(given_number, 1);
    printf("After setting bit %d\n", 1);
    print_binary(given_number);
    printf("After unsetting bit %d\n", 1);
    given_number = unset_kth_bit(given_number, 1);
    print_binary(given_number);
    printf("After toggling bit %d\n", 1);
    given_number = toggle_kth_bit(given_number, 1);
    print_binary(given_number);
    return 0;
}
