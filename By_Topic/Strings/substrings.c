/*
i
sairam
012345
j

i = 0, j = 0
i = 0, j = 1
i = 0, j = 2
i = 0, j = 3

*/
#include <stdio.h>
#include <string.h>

// void print(char* str, int start, int end)
// {
//     int len = end - start;
//     int i, j;
//     i = start, j = start;
//     while (len > 0) {
//         for (i = start; i <= j; i++) {
//             printf("%c", str[i]);
//         }
//         j++;
//         printf("\n");
//         len--;
//     }
// }

void print_substring(char* str)
{
    int len = strlen(str) - 1;
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            for (int k = i; k <= j; k++) {
                printf("%c", str[k]);
            }
            printf("\n");
        }
    }
}

int main(int argc, char const *argv[])
{
    char str[100];
    fgets(str, 100, stdin);
    // print(str, 0, strlen(str) - 1);
    print_substring(str);
    return 0;
}
