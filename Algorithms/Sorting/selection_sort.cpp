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
    int l = 0, r = 0;
    int mini_idx = 0;
    int min = 0; 
    while (l < len) {
        mini_idx = l;
        r = l+1;
        while (r < len) {
            if (arr[r] < arr[mini_idx]) {
                mini_idx = r;
            }
            r++;
        }
        swap(arr[mini_idx], arr[l]);
        l++;
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
