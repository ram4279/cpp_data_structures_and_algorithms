#include <bits/stdc++.h>
using namespace std;

void merge(int* arr1, int* arr2, int* res, int len1, int len2, int len3)
{
    int idx1 = 0, idx2 = 0, idx3 = 0;
    while (idx1 < len1 && idx2 < len2) {
        if (arr1[idx1] < arr2[idx2]) {
            res[idx3++] = arr1[idx1++];
        } else {
            res[idx3++] = arr2[idx2++];
        }
    }

    while (idx1 < len1) {
        res[idx3++] = arr1[idx1++];
    }

    while (idx2 < len2) {
        res[idx3++] = arr2[idx2++];
    }
}

int main(int argc, char const *argv[])
{
    int arr1[] = {1,3,5,7};
    int arr2[] = {2,4,8,10};
    int len1 = sizeof(arr1)/sizeof(arr1[0]);
    int len2 = sizeof(arr2)/sizeof(arr2[0]);
    int len3 = len1 + len2;
    int res[len3] = {0};
    merge(arr1, arr2, res, len1, len2, len3);
    for (int i = 0; i < len3; i++) {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}
