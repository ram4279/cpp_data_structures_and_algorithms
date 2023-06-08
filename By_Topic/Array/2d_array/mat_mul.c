#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void matrix_multiplication(int **a, int **b, int **c, int r1, int c1, int r2, int c2)
{
    // Check if the matrices are compatible for multiplication.
    if (c1 != r2)
    {
        printf("The matrices are not compatible for multiplication.\n");
        return;
    }

    // Multiply the matrices element-wise.
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < c1; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main()
{
    // Get the sizes of the matrices.
    int r1, r2, c1, c2;
    printf("Enter the number of rows in the first matrix: ");
    scanf("%d", &r1);
    printf("Enter the number of columns in the first matrix: ");
    scanf("%d", &c1);
    printf("Enter the number of rows in the second matrix: ");
    scanf("%d", &r2);
    printf("Enter the number of columns in the second matrix: ");
    scanf("%d", &c2);

    // Create the matrices.
    int **a = malloc(r1 * sizeof(int *));
    for (int i = 0; i < r1; i++)
    {
        a[i] = malloc(c1 * sizeof(int));
    }
    int **b = malloc(r2 * sizeof(int *));
    for (int i = 0; i < r2; i++)
    {
        b[i] = malloc(c2 * sizeof(int));
    }
    int **c = malloc(r1 * sizeof(int *));
    for (int i = 0; i < r1; i++)
    {
        c[i] = malloc(c2 * sizeof(int));
    }

    // Get the elements of the matrices.
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++)
        {
            printf("Enter the element at (%d, %d) of the first matrix: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 0; i < r2; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            printf("Enter the element at (%d, %d) of the second matrix: ", i, j);
            scanf("%d", &b[i][j]);
        }
    }

    // Multiply the matrices.
    matrix_multiplication(a, b, c, r1, c1, r2, c2);

    // Print the product matrix.
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    // Free the memory.
    for (int i = 0; i < r1; i++)
    {
        free(a[i]);
    }
    free(a);
    for (int i = 0; i < r2; i++)
    {
        free(b[i]);
    }
    free(b);
    for (int i = 0; i < r1; i++)
    {
        free(c[i]);
    }
    free(c);

    return 0;
}