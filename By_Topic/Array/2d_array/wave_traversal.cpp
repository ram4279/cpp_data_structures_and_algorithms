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
    direction_t d = DOWN;
    int down_end  = mat.size();
    int right_end = mat[0].size();
    int r = 0, c = 0;
    while (c < right_end) {
        cout << mat[r][c] << endl;
        if (d == DOWN) {
            r++;
            if (r == down_end) {
                d = UP;
                r = down_end - 1;
                c++;
            }
        } else if (d == UP) {
            r--;
            if (r == -1) {
                d = DOWN;
                r = 0;
                c++;
            }
        }
    }
    cout << endl;
    return;
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
    return 0;
}
