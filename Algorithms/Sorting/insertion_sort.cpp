#include <bits/stdc++.h>
using namespace std;

void printArray(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}



void insertion_sort(int* arr, int len)
{
    for (int i = 1; i < len; i++) {
        int cur = arr[i];
        int j;
        for (j = i - 1; j >= 0 && arr[j] > cur; j--) {
            arr[j+1] = arr[j];
        }
        arr[j+1] = cur;
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {5,4,3,2,1};
    
    int len = sizeof(arr)/sizeof(arr[0]);
    printArray(arr, len);
    insertion_sort(arr, len);
    printArray(arr, len);
    return 0;
}