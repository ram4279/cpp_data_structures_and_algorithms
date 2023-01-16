#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int *arr, int len)
{
    int gmax = INT_MIN;
    int cmax = 0;
    for (int i = 0; i < len; i++) {
        cmax += arr[i];
        if (cmax > gmax) {
            gmax = cmax;
        }

        if (cmax < 0) {
            cmax = 0;
        }
    }
    return gmax;
}

void print_maxSubArraySum(int *arr, int len)
{
    int gmax = INT_MIN;
    int cmax = 0;
    int start = 0, end = 0, cur_start = 0;
    for (int i = 0; i < len; i++) {
        cmax += arr[i];
        if (cmax > gmax) {
            gmax = cmax;
            start = cur_start;
            end = i;
        }

        if (cmax < 0) {
            cmax = 0;
            cur_start = i + 1;
        }
    }

    for (int i = start; i <=  end; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(a) / sizeof(a[0]);

    // Function Call
    int max_sum = maxSubArraySum(a, n);

    printf("Max sum = %d\n", max_sum);
    print_maxSubArraySum(a, n);
    return 0;
}
