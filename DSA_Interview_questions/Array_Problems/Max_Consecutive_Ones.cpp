/*
 * Given a binary array nums, return the maximum number of consecutive 1's in the array.
 *
 * Input: nums = [1,1,0,1,1,1]
 * Output: 3
 * Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.
 */

#include <iostream>

using namespace std;

int main()
{
    int n, i;
    int curr_window_size = 0;
    int max_window_size = 0;

    cin >> n;
    
    if (n <= 0) {
        return 0;
    }

    int arr[n] = { 0 };

    for (i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (i = 0; i < n; i++) {
        if (arr[i] != 0) {
            curr_window_size += 1;
            max_window_size = (max_window_size < curr_window_size) ? curr_window_size : max_window_size;
        } else {
            curr_window_size = 0;
        }
    }

    cout << "maximum number of consecutive 1's " << max_window_size << endl;
    return 0;
}
