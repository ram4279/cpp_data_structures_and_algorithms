#include <iostream>
#include <cmath>

using namespace std;

bool is_sorted(int *arr, int size)
{
    if (size == 1) {
        return true;
    }

    if (arr[0] > arr[1]) return false;
    
    return is_sorted(arr+1, size-1);
}

int main(int argc, char const *argv[])
{
    int arr[] ={1,2,3,4,5};
    cout << is_sorted(arr, 5) << endl;
    int arr2[] ={1,2,3,3,5,4,5};
    cout << is_sorted(arr2, 7) << endl;
    int arr3[] = {1,2,3,4,5,9};
    cout << is_sorted(arr3, 6) << endl;
    return 0;
}
