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

void rotate(int n, vector<vector<int>>& arr)
{
    int max_r = n, max_c = n,min_r = 0, min_c = 0;
    for (int c = 0; c < max_c; c++) {
        for (int r = n - 1; r >= 0; r--) {
            cout << arr[r][c] << "\t";
        }
        cout << endl;
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
}