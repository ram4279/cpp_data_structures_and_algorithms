#include <iostream>
#include <vector>
using namespace std;

void print_comb_sum(int idx, int* arr, int arr_len, int sum, vector<int>& list)
{
    if (idx >= arr_len) {
        if (sum == 0) {
            for (auto e: list) {
                cout << e << " ";
            }
            cout << endl;
        }
        return;
    }

    sum -= arr[idx];
    list.push_back(arr[idx]);
    print_comb_sum(idx + 1, arr, arr_len, sum, list);
    sum += arr[idx];
    list.pop_back();
    print_comb_sum(idx + 1, arr, arr_len, sum, list);
}

int get_sub_seq_count(int idx, int* arr, int arr_len, int sum)
{
    if (idx == arr_len) {
        if (sum == 0) {
            return 1;
        } else {
            return 0;
        }
    }
    sum = sum - arr[idx];
    int pick = get_sub_seq_count(idx + 1, arr, arr_len, sum);
    sum = sum + arr[idx];
    int not_pick = get_sub_seq_count(idx + 1, arr, arr_len, sum);
    return pick + not_pick;
}

bool get_one_sub_seq(int idx, int* arr, int arr_len, vector<int>& list, int sum)
{
    if (idx == arr_len) {
        if (sum == 0) {
            for (auto e: list) {
                cout << e << " ";
            }
            cout << endl;
            return true;
        } else {
            return false;
        }
    }

    sum -= arr[idx];
    list.push_back(arr[idx]);
    if (true == get_one_sub_seq(idx+1, arr, arr_len, list, sum)) {
        return true;
    }

    sum += arr[idx];
    list.pop_back();
    if (true == get_one_sub_seq(idx+1, arr, arr_len, list, sum)) {
        return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    int arr[] = {1,2,3,4,1};
    int sum = 6;
    int len = sizeof(arr)/sizeof(arr[0]);
    vector<int> list;
    print_comb_sum(0, arr, len, sum, list);

    int subseq_sum_count = get_sub_seq_count(0, arr, len, sum);
    cout << "No of subsequences " << subseq_sum_count << endl;

    list.clear();
    get_one_sub_seq(0, arr, len, list, sum);
    return 0;
}


