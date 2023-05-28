#include <bits/stdc++.h>
using namespace std;

template <size_t N>
void printArray(int (&a)[N]) {
    for (int i : a) {
        cout << i << " ";
    }
    cout << endl;
}


void selection_sort(int* arr, int len)
{
    
    for (int i = 0; i < len; i++) {
        int smallest_index = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[smallest_index] > arr[j]) {
                smallest_index = j;
            }
        }
        swap(arr[smallest_index], arr[i]);
    }
}


int main(int argc, char const *argv[])
{
    int arr[] = {5,5,4,4,3,3,2,2,1};
    printArray(arr);
    int len = sizeof(arr)/sizeof(arr[0]);
    selection_sort(arr, len);
    printArray(arr);
    return 0;
}
