#include <iostream>
using namespace std;

const int mr = 100, mc = 100;

typedef enum
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
} direction_t;

int **input(int **mat, int n, int m)
{
    mat = new int *[n];
    for (int i = 0; i < n; i++)
    {
        int *arr = new int[m];
        for (int j = 0; j < m; j++)
        {
            cin >> arr[j];
        }
        mat[i] = arr;
    }
    return mat;
}

int main(int argc, char **argv)
{
    int n, m;
    cin >> n >> m;
    int **mat = input(mat, n, m);

    // write your code here
    direction_t direction = RIGHT;

    int x = 0, y = 0;

    while (true) {

        if (direction == RIGHT) {
            y++;
        } else if (direction == DOWN) {
            x++;
        } else if (direction == UP) {
            x--;
        } else if (direction == LEFT) {
            y--;
        }

        if (direction == RIGHT && mat[x][y]) {
            direction = DOWN;
        } else if (direction == DOWN && mat[x][y]) {
            direction = LEFT;
        } else if (direction == LEFT && mat[x][y]) {
            direction = UP;
        } else if (direction == UP && mat[x][y]) {
            direction = RIGHT;
        }

        if (x < 0) {
            x++;
            break;
        } else if (y < 0) {
            y++;
            break;
        } else if (x == n) {
            x--;
            break;
        } else if (y == m) {
            y--;
            break;
        }
    }

    cout << x << "," << y << endl;

    return 0;
}