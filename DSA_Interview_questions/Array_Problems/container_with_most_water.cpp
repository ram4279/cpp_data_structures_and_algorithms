/*
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

Example 1:
==========
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. 
In this case, the max area of water the container can contain is 49.
*/

#include <bits/stdc++.h>
using namespace std;

int maxArea_bruteforce(vector<int>& hts) {
    if (hts.size() <= 1) {
        return 0;
    }
    int res_area = INT_MIN;
    for (int i = 0; i < hts.size(); i++) {
        for (int j = i+1; j < hts.size(); j++) {
            int height = min(hts[i], hts[j]);
            int width  = j - i;
            int area = height * width;
            res_area = max(area, res_area);
        }
    }
    return res_area;
}

int maxArea(vector<int>& hts) {
    if (hts.size() <= 1) {
        return 0;
    }
    int res_area = INT_MIN;
    int l = 0, r = hts.size() - 1;
    while(l < r) {
        int height = min(hts[l], hts[r]);
        int width  = r - l;
        int area = height * width;
        res_area = max(area, res_area);
        if (hts[l] < hts[r]) {
            l++;
        } else {
            r++;
        }
    }
    return res_area;
}