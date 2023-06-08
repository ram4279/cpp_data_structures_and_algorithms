#include <stdio.h>

int main() {
    int n, m;
    printf("Enter the number of rows: ");
    scanf("%d", &n);
    printf("Enter the number of columns: ");
    scanf("%d", &m);

    int a[n][m];
    printf("Enter the elements of the array (0s and 1s):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int dir = 0;  // 0 -> east, 1 -> south, 2 -> west, 3 -> north
    int i = 0, j = 0;

    while (i >= 0 && i < n && j >= 0 && j < m) {
        dir = (dir + a[i][j]) % 4;
        if (dir == 0) {
            j++;
        } else if (dir == 1) {
            i++;
        } else if (dir == 2) {
            j--;
        } else if (dir == 3) {
            i--;
        }

        if (i < 0) {
            i++;
            break;
        } else if (j < 0) {
            j++;
            break;
        } else if (j == m) {
            j--;
            break;
        } else if (i == n) {
            i--;
            break;
        }
    }

    printf("Exit point: (%d, %d)\n", i, j);

    return 0;
}
