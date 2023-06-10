/*
Traverse in spiral display right down left up  repeat
Sample Input
3
5
11 12 13 14 15
21 22 23 24 25
31 32 33 34 35
Sample Output
11
12
13
14
15
25
35
34
33
32
31
21
22
23
24
*/

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

int main(int argc, char **argv)
{
    int mat[mr][mc] = {0};
    int n, m;
    cin >> n >> m;

    inputBound(mat, n, m);
    print(mat, n, m);

    int min_r = 0, min_c = 0;
    int max_r = n - 1, max_c = m - 1;
    int cnt = 1;
    int total_elements = n * m;

    while (cnt < total_elements)
    {
        // top wall
        for (int i = min_c, j = min_r; i <= max_c; i++) {
            cout << mat[j][i] << endl;
            cnt++;
        }
        min_r++;

        // right wall
        for (int i = min_r, j = max_c; i <= max_r; i++) {
            cout << mat[i][j] << endl;
            cnt++;
        }
        max_c--;

        // bottom wall
        for (int i = max_c, j = max_r; i >= min_c; i--) {
            cout << mat[j][i] << endl;
            cnt++;
        }
        max_r--;

        // left wall
        for (int i = max_r, j = min_c; i >= min_r; i--) {
            cout << mat[i][j] << endl;
            cnt++;
        }
        min_c++;
    }

    return 0;
}