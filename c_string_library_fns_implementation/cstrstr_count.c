/**
 * Given a string and substr. Count the occurence of the
 * substr in the string 
 * 
 * Asked in one of my interviews
 * */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int count_substr(char* string, const char* substr)
{
    int count = 0;
    int string_len = strlen(string);
    int substr_len = strlen(substr);
    if (substr_len > string_len) {
        return 0;
    }
    bool found = true;
    for (int i = 0; i <= string_len - substr_len; i++) {
        found = true;
        for (int j = 0; j < substr_len; j++) {
            if (string[i+j] != substr[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            count++;
        }
    }
    return count;
}

int main(int argc, char const *argv[])
{
    int total_count = 0;

    if (argc != 3) {
        printf("Invalid arg count\n");
        printf("eg %s file2.txt string\n", argv[0]);
        return 0;
    }

    char buffer[2048] = {0};

    FILE* fp;
    fp = fopen(argv[1], "r");

    while (!feof(fp)) {
        fgets(buffer, sizeof(buffer), fp);
        total_count += count_substr(buffer, argv[2]);
    } 

#if 0
    char* string = "this is a this string that starts with this and ends with this";
    char* substr = "this";
    printf("res = %d\n", count_substr(string, substr));
#endif
    printf("res = %d\n", total_count);
    fclose(fp);
    return 0;
}
