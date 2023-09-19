/*
1. You are given a square matrix of size 'n'. You are given n*n elements of the square matrix.
2. You are required to find the saddle price of the given matrix and print the saddle price.
3. The saddle price is defined as the least price in the row but the maximum price in the column of the matrix.
1 2 3
4 5 7
2 3 9

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    int **arr = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = malloc(sizeof(int) * n);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    for (int r = 0; r < n; r++)
    {
        int min = 0;
        // Who is the minimum element
        for (int c = 1; c < n; c++)
        {
            if (arr[r][c] < arr[r][min])
            {
                min = c;
            }
        }

        // Is he the maximum ?
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (arr[i][min] > arr[r][min]) {
                flag = false;
                break;
            }
        }

        if (flag) {
            printf("%d", arr[r][min]);
            return 0;
        }
    }
    
    printf("%s", "NO SADDLE POINT\n");

    return 0;
}
