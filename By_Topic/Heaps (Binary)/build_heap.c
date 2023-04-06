#include <stdio.h>
#include <unistd.h>
#include <time.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int heapify(int* arr, int idx, int size)
{
    int smallest = idx;
    int li = 2 * idx + 1;
    int ri = 2 * idx + 2;

    if (li < size && arr[li] < arr[smallest]) {
        smallest = li;
    } else if (ri < size && arr[ri] < arr[smallest]) {
        smallest = ri;
    }

    if (smallest != idx) {
        swap(&arr[smallest], &arr[idx]);
        heapify(arr, smallest, size);
    }
}

void build_heap(int *arr, int size)
{
    int last_non_leaf_node = (size)/2 - 1;
    printf("last_non_leaf_node = %d\n", arr[last_non_leaf_node]);
    for (int i = last_non_leaf_node; i >= 0; i--) {
        heapify(arr, i, size);
    }
}

int main(int argc, char const *argv[])
{
    int size;
    printf("Enter the array size\n");
    scanf("%d", &size);
    int arr[size];
    printf("Enter array elemets\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Building heap....\n");
    build_heap(arr, size);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

