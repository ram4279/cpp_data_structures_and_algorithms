#include<iostream>
#include<vector>

using namespace std;

typedef enum 
{
    LEFT,
    RIGHT,
    UP,
    DOWN
} direction_t ;

void columnTraversal(vector<vector<int>> mat) {
    for (int i = 0; i < mat[0].size(); i++) {
        if (i & 1) {
            for (int j = mat.size() - 1; j >= 0; j--) {
                cout << mat[j][i] << endl;
            }
        } else {
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