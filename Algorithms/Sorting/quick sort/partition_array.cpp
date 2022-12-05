#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Remember there are three regions
0 - last => unknown
0 - j-1 => less than equal to pivot
j - i-1 => greater than pivot

i is the fast moving pointer in the below
*/


void partition(vector<int> &arr, int pivot)
{
    int i = 0, j = 0;
    while (i < arr.size()) {
        if (arr[i] > pivot) {
            i++;
        } else {
            swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }
}

int main()
{
    vector<int> vec {4,6,1,2,7,5,5,3,8};
    for (auto v: vec) {
        cout << v << " ";
    }
    cout << endl;
    partition(vec, 5);
    partition(vec, 4);
    partition(vec, 3);
    partition(vec, 2);
    partition(vec, 1);
    for (auto v: vec) {
        cout << v << " ";
    }
    cout << endl;
}

