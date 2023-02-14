
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


long long count_words(char* ptr)
{
    long long count = 0;
    char* file_path = ptr;
    // printf("file path = %s\n", file_path);
    FILE *fp = fopen(file_path, "r");
    char c;
    int prev_space = 1; //flag to keep track of the previous character
    while ((c = fgetc(fp)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            prev_space = 1;
        } else {
            if (prev_space) {
                (count)++;
            }
            prev_space = 0;
        }
    }
    fclose(fp);
    return count;
}


int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("eg: %s file1.txt file2.txt\n", argv[0]);
        return -1;
    }

    long long result = count_words(argv[0]);
    result += count_words(argv[1]);
    printf("No of words = %lld\n", result);
}
