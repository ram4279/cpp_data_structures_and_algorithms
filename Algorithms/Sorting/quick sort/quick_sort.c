#include <stdio.h>

#define SWAP(T, x, y) do { \
    T temp = x; \
    x = y; \
    y = temp; \
} while (0)\

int partition(int *arr, int low, int hi)
{
    int pivot = arr[hi];
    int i = low, j = low;
    while (i <= hi) {
        if (arr[i] > pivot) {
            i++;
        } else {
            SWAP(int, arr[i], arr[j]);
            i++;
            j++;
        }
    }
    return j - 1;
}
void quicksort(int *arr, int low, int hi)
{
    if (low < hi) {
        int pivot = partition(arr, low, hi);
        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot+1, hi);
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {24,3,41,23,52,15,1};
    int len = sizeof(arr)/sizeof(arr[0]);
    quicksort(arr,  0, len - 1);
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
