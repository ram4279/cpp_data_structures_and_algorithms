/*
Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
In this case, 6 units of rain water (blue section) are being trapped.

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9
*/
#include <bits/stdc++.h>
using namespace std;
int max_lb(vector<int> &hts, int pos) {
    int res = 0;
    while(pos >= 0) {
        res = max(res, hts[pos]);
        pos--;
    }
    return res;
}

int max_rb(vector<int> &hts, int pos) {
    int res = 0;
    while(pos < hts.size()) {
        res = max(res, hts[pos]);
        pos++;
    }
    return res;
}
int trap_bruteforce(vector<int> &hts) {
    int total = 0;
    for (int i = 0; i < hts.size(); i++) {
        int max_left_block       = max_lb(hts, i);
        int max_right_block      = max_rb(hts, i);
        int current_block_height = hts[i];
        int water_at_current_index = min(max_left_block, max_right_block) - current_block_height;
        total+=water_at_current_index;
    }
    return total;
}
