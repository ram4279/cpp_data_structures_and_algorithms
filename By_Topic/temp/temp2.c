#include <stdio.h>

int titleToNumber(char * columnTitle){
    char* ptr = columnTitle;
    int len = strlen(columnTitle);
    int res = 0;
    for (int i = len; i >= 0 && ptr; i++, ptr++) {
        res += ((int)pow(26, len)) * (*ptr - 'A');
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int letter_count[27] = {0};
    for (size_t i = 0; i < 27; i++)
    {
        printf("%d ", letter_count[i]);
    }
    printf("\n");
    return 0;
}
