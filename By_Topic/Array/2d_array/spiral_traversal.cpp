#include <iostream>
using namespace std;

const int mr = 100, mc = 100;
void inputBound(int (&mat)[mr][mc], int n, int m)
{

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cin >> mat[i][j];
    }
  }
}


void print(const int (&mat)[mr][mc], int n, int m)
{

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }
}

int main(int argc, char** argv)
{
    int mat[mr][mc] = {0};
    int n, m;
    cin >> n >> m;

    inputBound(mat, n, m);
    print(mat, n, m);

    int min_r = 0, min_c = 0;
    int max_r = n - 1, max_c = m - 1;
    int cnt = 1;
    int total_elements = n*m;

    while (cnt < total_elements)
    {
        // left wall
        for (int i = min_r, j = min_c; i <= max_r; i++) {
            cout << mat[i][j] << endl;
            cnt++;
        }
        min_c++;

        // bottom wall
        for (int i = min_c, j = max_r; i <= max_c; i++) {
            cout << mat[j][i] << endl;
            cnt++;
        }
        max_r--;

        // right wall
        for (int i = max_r, j = max_c; i >= min_r; i--) {
            cout << mat[i][j] << endl;
            cnt++;
        }
        max_c--;

        // top wall     
        for (int i = max_c, j = min_r; i >= min_c; i--) {
            cout << mat[j][i] << endl;
            cnt++;
        }
        min_r++;
    }


    return 0;
}