#include <iostream>
using namespace std;

void print_all_index(int *arr, int n, int i, int x)
{
    if (i == n) {
        return;
    }

    if (arr[i] == x) {
        cout << i << endl;
    }

    print_all_index(arr, n, i+1, x);
}

int main()
{
    int arr[] = {1,7,2,3,4,5,7};
    int n = sizeof(arr)/sizeof(arr[0]);
    print_all_index(arr, n, 0, 7);
    return 0;
}