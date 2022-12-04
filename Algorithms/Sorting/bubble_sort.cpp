#include <bits/stdc++.h>
using namespace std;

template <size_t N>
void printArray(int (&a)[N]) {
    for (int i : a) {
        cout << i << " ";
    }
    cout << endl;
}

void bubble_sort(int* arr, int len)
{
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
    return;
}

int main(int argc, char const *argv[])
{
    int arr[] = {5,5,4,4,3,3,2,2,1};
    printArray(arr);
    int len = sizeof(arr)/sizeof(arr[0]);
    bubble_sort(arr, len);
    printArray(arr);
    return 0;
}
