/*
Sample Input
4
11 12 13 14
21 22 23 24
31 32 33 34
41 42 43 44
Sample Output
41 31 21 11
42 32 22 12
43 33 23 13
44 34 24 14

4
00 01 02 03
10 11 12 13
20 21 22 23
30 31 32 33

30 20 10 00
31 21 11 01
32 22 12 02
33 23 13 03
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print_vector(const vector<vector<int>> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[i].size(); j++)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void rotate(int n, vector<vector<int>> &arr)
{
    print_vector(arr);
    // First transpose the matrix
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = i; j < arr[i].size(); j++)
        {
            swap(arr[i][j], arr[j][i]);
        }
    }

    // Reverse the columns of the matrix
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[0].size() / 2; j++)
        {
            swap(arr[i][j], arr[i][arr[i].size() - j - 1]);
        }
    }
    
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> arr(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
    rotate(n, arr);
    print_vector(arr);
}