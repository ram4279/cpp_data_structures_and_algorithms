#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char* ptr[] = {"ITEM1", "ITEM2", "ITEM3"};

    /* Copying contents from ptr(array of char pointers) to copy (2d array) */
    char copy[3][12] = {0};
    for (int i = 0; i < 3; i++) {
        strcpy(copy[i], ptr[i]);
    }

    /* Copying Copying contents from ptr(array of char pointers) to copy2 (array of char pointers) */
    char* copy2[3] = { NULL };
    for (int i = 0; i < 3; i++) {
       copy2[i] = ptr[i];
    }

    /* Copying contents from ptr(array of char pointers) to copy3 (2d array in head) */
    char** copy3 = (char**)malloc(3*sizeof(char*));
    for (int i = 0; i < 3; i++)
    {
        copy3[i] = malloc(12*sizeof(char));
        strcpy(copy3[i], ptr[i]);
    }
    
    for (int i = 0; i < 3; i++) {
        printf("copy[%d] = %s\n", i, copy[i]);
    }

    for (int i = 0; i < 3; i++) {
        printf("copy2[%d] = %s\n", i, copy2[i]);
    }

    for (int i = 0; i < 3; i++) {
        printf("copy3[%d] = %s\n", i, copy3[i]);
    }
    
    return 0;
}