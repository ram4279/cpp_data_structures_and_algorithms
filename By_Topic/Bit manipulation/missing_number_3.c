/**
 * Find the two non-repeating elements in an array of repeating elements/ Single Number III
 * arr <- [1,1,2,5,3,2,3,4,7,4]
 * res <- 5, 7
 */

#include <stdio.h>

typedef struct pts
{
    int x;
    int y;
} pts_t;


struct pts find_non_repeating_elements(int arr[], int len)
{
    int xor_result = 0;
    for (size_t i = 0; i < len; i++) {
        xor_result ^= arr[i];
    }

    int rsb_mask = (xor_result & -xor_result);
    pts_t res;
    res.x = 0;
    res.y = 0;

    for (int i = 0; i < len; i++) {
        if ((arr[i] & rsb_mask) == 0) {
            res.x ^= arr[i]; // This will have all the elements thats are not having rsbmask set
        } else {
            res.y ^= arr[i]; // This will have all the elements thats having rsbmask set
        }
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int arr[] = {1,1,2,5,3,2,3,4,7,4};
    int len = sizeof(arr)/sizeof(arr[0]);
    pts_t res = find_non_repeating_elements(arr, len);
    printf("Non repeating element x = %d, y = %d\n", res.x, res.y);
    return 0;
}
