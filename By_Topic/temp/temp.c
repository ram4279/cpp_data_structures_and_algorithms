#include <stdio.h>

int main(int argc, char const *argv[])
{
    int num, sum = 0;
    FILE* fp = fopen("./temp.txt", "r");
    fscanf(fp, "%d", &num);
    while (num != 0)
    {
        fscanf(fp, "%d", &num);
        sum = sum + num;
    }

    printf("Sum of entered numbers = %d\n", sum);
    
    return 0;
}
