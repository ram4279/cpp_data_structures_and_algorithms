#include <iostream>
#include <cmath>

using namespace std;

int sum_of_arr(int *arr, int size)
{
    if (size == 1) {
        return arr[0];
    }

    int smaller_arr_size = sum_of_arr(arr + 1, size - 1);
    return arr[0] + smaller_arr_size; 

}

int main(int argc, char const *argv[])
{
    int arr[] ={1,2,3,4,5};
    cout << sum_of_arr(arr, 5) << endl;
    int arr2[] ={1,2,3,3,5,4,5};
    cout << sum_of_arr(arr2, 7) << endl;
    int arr3[] = {1,2,3,4,5,9};
    cout << sum_of_arr(arr3, 6) << endl;
    return 0;
}
