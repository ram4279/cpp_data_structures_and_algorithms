/*
Given an array A[] of n numbers and another number x, the task is to check whether or not there exist
two elements in A[] whose sum is exactly x. 

Examples: 

Input: arr[] = {0, -1, 2, -3, 1}, x= -2
Output: Yes
Explanation:  If we calculate the sum of the output,1 + (-3) = -2

Input: arr[] = {1, -2, 1, 0, 5}, x = 0
Output: No
*/
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n,k;
    bool found = false;
    cin >> k; 
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr+n);
    int l = 0, r = n - 1;

    while (l < r) {
        int sum = arr[l] + arr[r];
        if (sum > k) {
            r--;
        } else if (sum < k) {
            l++;
        } else {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;

}
