/**
 * Read two files and count the number of space separated words in each file
 * Each file should be read by one thread
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* count_words(void* arg)
{
    long long *count = calloc(1, sizeof(long long));
    char* file_path = (char*)arg;
    // printf("file path = %s\n", file_path);
    FILE *fp = fopen(file_path, "r");
    char c;
    int prev_space = 1; //flag to keep track of the previous character
    while ((c = fgetc(fp)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            prev_space = 1;
        } else {
            if (prev_space) {
                (*count)++;
            }
            prev_space = 0;
        }
    }

    return count;
    fclose(fp);
}

int main(int argc, char const *argv[])
{

    long long *ptr1, *ptr2;
    if (argc != 3) {
        printf("eg: %s file1.txt file2.txt\n", argv[0]);
        return -1;
    }

    pthread_t th1, th2;

    char* filepath1 = malloc(120);
    char* filepath2 = malloc(120);

    strcpy(filepath1, argv[1]);
    strcpy(filepath2, argv[2]);

    if (pthread_create(&th1, NULL, count_words, (void *)filepath1)) {
        return -1;
    }

    if (pthread_create(&th2, NULL, count_words, (void *)filepath2)) {
        return -1;
    }



    if (pthread_join(th1, (void**)&ptr1)) {
        return -1;
    }

    if (pthread_join(th2, (void**)&ptr2)) {
        return -1;
    }

    // printf("NO OF WORDS IN FILE1 = %lld\n", *ptr1);
    // printf("NO OF WORDS IN FILE2 = %lld\n", *ptr2);

    long long result = *ptr1 + *ptr2;

    printf("No of words = %lld\n", result);

    free(filepath1);
    free(filepath2);
    free(ptr1);
    free(ptr2);

    return 0;
}
