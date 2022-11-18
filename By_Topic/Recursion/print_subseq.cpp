#include <bits/stdc++.h>
using namespace std;

void print_subseq(int idx, int* arr, vector<int> &list, int len)
{
    if (idx >= len) {
        for (auto i: list) {
            cout << i << " ";
        }
        cout << endl;
        return;
    }
    list.push_back(arr[idx]);
    print_subseq(idx+1, arr, list, len);
    list.pop_back();
    print_subseq(idx+1, arr, list, len);
    return;
}

void combine_r(int idx, int n, int k, vector<int>& list, vector<vector<int>> &res)
{
    if (list.size() == k) {
        res.push_back(list);
        return;
    }

    if (idx == n) {
        if (list.size() == k) {
            res.push_back(list);
            return;
        }
    }

    if (idx > n) {
        return;
    }

    list.push_back(idx);
    combine_r(idx+1,n,k, list, res);
    list.pop_back();
    combine_r(idx+1,n,k, list, res);
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> list;
    combine_r(1, n, k, list, res);
    for (auto tlist: res) {
        for (auto e: tlist) {
            cout << e << " ";
        }
        cout << endl;
    }
    return res;
}



int main(int argc, char const *argv[])
{
    int arr[] = {1,2,3,4};
    vector<int> list;
    print_subseq(0, arr, list, 4);
    combine(4,2);
    return 0;
}
