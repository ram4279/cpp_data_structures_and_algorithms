#include <stdio.h>

void merge(int *arr, int low, int mid, int high)
{
    int temp[high - low + 1];
    int i = 0, j = mid + 1;
    int k = 0;
    while (i <= mid && j <= high)
    {
        if (arr[i] < arr[j])
        {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }


    while (i <= mid) temp[k++] = arr[i++];
    while (j <= high) temp[k++] = arr[j++];
    for (i = low, k = 0; i <= high; i++, k++)
    {
        arr[i] = temp[k];
    }
}

void merge_sort(int *arr, int low, int high)
{
    if  (low >= high) return;
    int mid = (high + low)/2;
    merge_sort(arr, low, mid);
    merge_sort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}
int main()
{
    int arr[] = {5,3,2,1,5,3,5};
    int len = sizeof(arr)/sizeof(arr[0]);

    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    merge_sort(arr, 0, len - 1);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

