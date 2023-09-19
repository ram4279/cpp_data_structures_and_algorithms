#include <iostream>
using namespace std;

int count_occurence_of_x(int *arr, int n, int i, int x)
{
    if (i == n) {
        return 0;
    }

    if (arr[i] == x) {
        return 1 + count_occurence_of_x(arr, n, i+1, x);
    } else {
        return count_occurence_of_x(arr, n, i+1, x);
    }
}


int main()
{
    int arr[] = {1,7,2,7,3,4,5,7};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << count_occurence_of_x(arr, n, 0, 7) << endl;
    return 0;
}