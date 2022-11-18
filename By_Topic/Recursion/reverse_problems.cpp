#include <bits/stdc++.h>
using namespace std;

void reverse_2(int* arr, int n, int idx)
{
    if (idx >= n/2) {
        return;
    }
    swap(arr[idx], arr[n-idx-1]);
    reverse_2(arr, n, idx+1);
}

void reverse_r(int* arr, int left, int right)
{
    if (left >= right) {
        return;
    }
    swap(arr[left], arr[right]);
    reverse_r(arr, left+1, right-1);
}

bool is_pal(string word, int len, int idx)
{
    if (idx >= len/2) {
        return true;
    }

    if (word[idx] != word[len-idx-1]) {
        return false;
    }
    return is_pal(word, len, idx+1);
}


int main(int argc, char const *argv[])
{
    int arr[] = {5, 4, 3, 2, 1};
    int len = sizeof(arr)/sizeof(arr[0]);
    reverse_r(arr, 0, len - 1);
    for(auto a: arr) {
        cout << a << " ";
    }
    reverse_r(arr, len, 0);
    cout << endl;

    reverse_2(arr, len, 0);
    for(auto a: arr) {
        cout << a << " ";
    }
    cout << endl;

    string word{"malaylam"};
    if (is_pal(word, word.length(), 0)) {
        cout << "Given word is palindrome" << endl;
    } else {
        cout << "Given word is not a palindrome" << endl;
    }

    return 0;
} 
