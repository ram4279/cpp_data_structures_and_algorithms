/*
Input
R = 5
C = 7
S = 2
R = 3
11 12 13 14 15 16 17
21 22 23 24 25 26 27
31 32 33 34 35 36 37
41 42 43 44 45 46 47
51 52 53 54 55 56 57

OP
11 12 13 14 15 16 17
21 25 26 36 46 45 27
31 24 33 34 35 44 37
41 23 22 32 42 43 47
51 52 53 54 55 56 57
*/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

void printArray(int **arr, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void reverse(int *arr, int start, int end)
{
    end--;
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotate_1d_array(int *arr, int rotations, int size)
{
    rotations = rotations % size;
    reverse(arr, 0, size - rotations);
    reverse(arr, size - rotations, size);
    reverse(arr, 0, size);
}

int *get_one_d_array(int **arr, int r, int c, int shell_idx, int *new_array_size)
{
    int min_r, min_c;
    min_r = min_c = shell_idx - 1;
    int max_r = r - shell_idx;
    int max_c = c - shell_idx;
    /*
     * size = left_wall_elements + right_wall_elements + top_wall_elements + bottom_wall_elements
     *         - (4 duplicate elements at 4 corners)
     */
    *new_array_size = 2 * (max_r - min_r + max_c - min_c);
    int *new_one_d_array = malloc(sizeof(int) * (*new_array_size));

    int idx = 0;

    // left wall
    for (int i = min_r, j = min_c; i <= max_r; i++)
    {
        new_one_d_array[idx++] = arr[i][j];
    }

    // bottom wall
    for (int i = min_c + 1, j = max_r; i <= max_c; i++)
    {
        new_one_d_array[idx++] = arr[j][i];
    }

    // right wall
    for (int i = max_r - 1, j = max_c; i >= min_r; i--)
    {
        new_one_d_array[idx++] = arr[i][j];
    }

    // top wall
    for (int i = max_c - 1, j = min_r; i >= min_c + 1; i--)
    {
        new_one_d_array[idx++] = arr[j][i];
    }

    return new_one_d_array;
}

void update_shell(int **arr, int r, int c, int *one_d_array, int size, int shell_idx)
{
    int min_r, min_c;
    min_r = min_c = shell_idx - 1;
    int max_r = r - shell_idx;
    int max_c = c - shell_idx;

    // left wall
    int idx = 0;
    for (int i = min_r, j = min_c; i <= max_r; i++)
    {
        arr[i][j] = one_d_array[idx++];
    }

    // bottom wall
    for (int i = min_c + 1, j = max_r; i <= max_c; i++)
    {
        arr[j][i] = one_d_array[idx++];
    }

    // right wall
    for (int i = max_r - 1, j = max_c; i >= min_r; i--)
    {
        arr[i][j] = one_d_array[idx++];
    }

    // top wall
    for (int i = max_c - 1, j = min_r; i >= min_c + 1; i--)
    {
        arr[j][i] = one_d_array[idx++];
    }
}

void print_1d_arr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void shell_rotate(int **arr, int r, int c, int shell_idx, int rotations)
{
    int new_array_size;
    int *new_arr = get_one_d_array(arr, r, c, shell_idx, &new_array_size);
#ifdef DEBUG
    print_1d_arr(new_arr, new_array_size);
#endif
    rotate_1d_array(new_arr, rotations, new_array_size);
#ifdef DEBUG
    print_1d_arr(new_arr, new_array_size);
#endif
    update_shell(arr, r, c, new_arr, new_array_size, shell_idx);
    free(new_arr);
}
int main()
{
    int r, c;
    scanf("%d %d", &r, &c);
    int **arr = malloc(sizeof(int *) * r);
    for (int i = 0; i < c; i++)
    {
        arr[i] = malloc(sizeof(int) * c);
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    int shell, rotations;
    scanf("%d %d", &shell, &rotations);

    printArray(arr, r, c);
    shell_rotate(arr, r, c, shell, rotations);
    printArray(arr, r, c);
}