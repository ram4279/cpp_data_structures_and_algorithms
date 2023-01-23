#include <stdio.h>

#define MAX_BUFF_SIZE 1024


int mstrlen(char* str)
{
    int len = 0;
    while (*str) {
        len++;
        str++;
    }
    return len;
}

int main(int argc, char const *argv[])
{
    char num1[MAX_BUFF_SIZE] = {0};
    char num2[MAX_BUFF_SIZE] = {0};
    char res[MAX_BUFF_SIZE + 1] = {0};


    scanf("%s", num1);
    scanf("%s", num2);

    int len1 = mstrlen(num1);
    int len2 = mstrlen(num2);

    len1--;
    len2--;

    printf("Len1 = %d\n", len1);
    printf("Len2 = %d\n", len2);

    int resptr = 0;
    int carry = 0;
    int n1 = 0;
    int n2 = 0;
    char c;

    while (len1 >= 0 || len2 >= 0 || carry == 1) {
        if (len1 >= 0) {
            n1 = num1[len1] - '0';
        } else {
            n1 = 0;
        }
        if (len2 >= 0) {
            n2 = num2[len2] - '0';
        } else {
            n2 = 0;
        }

        int sum = n1 + n2 + carry;
        carry = sum / 10;
        sum = sum % 10;
        res[resptr] = sum + '0';
        len1--;
        len2--;
        resptr++;
    }

    for (int i = resptr; i >= 0; i--) {
        printf("%c", res[i]);
    }

    printf("\n");

    return 0;
}