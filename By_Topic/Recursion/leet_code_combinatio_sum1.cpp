class Solution {
public:
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> list;
        combinationSum_h(0, candidates, target, result, list);
        return result;
    }

    void combinationSum_h(int idx, vector<int>& candidates, int target, vector<vector<int>>& result,vector<int> &list) {
        if (idx == candidates.size()) {
            if (target == 0) {
                result.push_back(list);
                return;
            }
            return;
        }

        if (target > 0) {
            target -= candidates[idx];
            // Select the same element again and again until target matches or not matches
            list.push_back(candidates[idx]);
            combinationSum_h(idx, candidates,target, result, list);
        } else if (target == 0) {
            result.push_back(list);
            return;
        } else {
            return;
        }

        target += candidates[idx];
        list.pop_back();
        combinationSum_h(idx + 1, candidates, target, result, list);
    }
};