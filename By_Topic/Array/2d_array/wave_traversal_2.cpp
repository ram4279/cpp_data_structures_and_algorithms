/*
Sample Input
3
4
11 12 13 14 
21 22 23 24
31 32 33 34
Sample Output
11
21
31
32
22
12
13
23
33
34
24
14
*/

#include<iostream>
#include<vector>

using namespace std;

void columnTraversal(vector<vector<int>> mat) {
    for (int i = 0; i < mat[0].size(); i++) {
        if (i & 1) { // Odd columsn go upward
            for (int j = mat.size() - 1; j >= 0; j--) {
                cout << mat[j][i] << endl;
            }
        } else { // Even columns go downward
            for (int j = 0; j < mat.size(); j++) {
                cout << mat[j][i] << endl;
            }
        }
    }
}

int main() {
  int n;
  int m;
  cin >> n;
  cin >> m;

  vector<vector<int>> mat;
  for (int i = 0; i < n; i++) {
    vector<int> arr;
    for (int j = 0; j < m; j++) {
      int ele;
      cin >> ele;
      arr.push_back(ele);
    }
    mat.push_back(arr);
  }

  columnTraversal(mat);
}