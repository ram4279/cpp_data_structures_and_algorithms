/*
r_l -> 1 2 3
       4 5 6
       7 8 9
r_h -> 10 11 12

mid = (r_l + r_h) / 2
mid = arr[1][0]

*/

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    int r, c;
    cin >> r >> c;

    vector<vector<int>> arr(r, vector<int>(c));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> arr[i][j];
        }
    }

    int x;
    cin >> x;

    int i = 0;
    int j = c - 1;

    while (i < r && j >= 0 )
    {
        if (arr[i][j] == x)
        {
            cout << "Element is at " << i << " " << j << endl;
            return 1;
        } else if (x > arr[i][j]) {
            i++; // Search in the next row
        } else {
            j--; // Search in the previous column
        }
    }

    cout << "Element not found " << endl;
    return 0;
}
