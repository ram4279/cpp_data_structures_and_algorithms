#include <bits/stdc++.h>
using namespace std;

void printArray(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}



/**
 * p -> prev
 * c -> curr
 * 
 * p c=3
 * | 
 * 4 3 2 1
 * 
 * 4 4 2 1
 * 
 * 3 4 2 1
 * 
 *   p c=2
 *   |   
 * 3 4 2 1
 * 
 * p
 * |
 * 3 4 4 1
 * 
 *
 * 3 3 4 1
 * 
 * 2 3 4 1
 */
void insertion_sort(int* arr, int len)
{
    for (int i = 1; i < len; i++) {
        int cur = arr[i];
        int prev;
        for (prev = i - 1; prev >= 0 && arr[prev] > cur; prev--) {
            arr[prev+1] = arr[prev];
        }
        arr[prev+1] = cur;
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {5,4,3,2,1,0,1,2,3,4,5};
    
    int len = sizeof(arr)/sizeof(arr[0]);
    printArray(arr, len);
    insertion_sort(arr, len);
    printArray(arr, len);
    return 0;
}