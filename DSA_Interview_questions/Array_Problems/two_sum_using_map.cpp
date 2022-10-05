/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

Example 1:
=========
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
=========
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
=========
Input: nums = [3,3], target = 6
Output: [0,1]

*/
#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int> &nums, int target)
{
    vector<int> res;
    unordered_map<int, int> umap; // element, index

    for (int i = 0; i < nums.size(); i++)
    {
        // Get complement
        // array - [2,7,11,15]
        // comp  - [7,2,-2,-4]
        int no_to_find = target - nums[i]; // find functions searches for key not values
        // Check complement exists in map
        auto search = umap.find(no_to_find);
        if (search != umap.end()) {
            //Complement Exists  update indeces
            res.push_back(i);
            res.push_back(search->second);
            return res;
        } else {
            //Add current element along with its index in the table
            umap.insert({nums[i], i});
        }
    }
    return res;
}


int main(int argc, char const *argv[])
{
    vector<int> input{2, 7, 11, 15};
    auto res = twoSum(input, 9);
    cout << res[0] << " " << res[1] << endl;
    return 0;
}
