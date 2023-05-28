#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_NAMES       8

void parallelSort(int lo, int hi, int max, char list[][max], int id[]) {
//Sort the names in list[lo] to list[hi] in alphabetical order, ensuring
//that each name remains with its original id number.
//The maximum string size is max - 1 (one char taken up by \0).
    char key[max];
    for (int h = lo + 1; h <= hi; h++) {
        strcpy(key, list[h]);
        int m = id[h];  // extract the id number
        int k = h - 1; //start comparing with previous item
        while (k >= lo && strcmp(key, list[k]) < 0) {
            strcpy(list[k + 1], list[k]);
            id[k+ 1] = id[k];  // move up id when we move a name
            --k;
        }
        strcpy(list[k + 1], key);
        id[k + 1] = m; // store id in the same position as the name
    } //end for
} //end parallelSort

int main(int argc, char const *argv[])
{
    char names[MAX_NAMES][MAX_NAME_LENGTH] = {
        "Samlal, Rawle", "Williams, Mark","Delwin, Mac",
        "Taylor, Victor", "Mohamed, Abu","Singh, Krishna",
        "Tawari, Tau", "Abdool, Zaid"
    };

    int ids[MAX_NAMES] = {
        8742,5418,4833,4230,8583,2458,5768,3313
    };

    parallelSort(0, MAX_NAMES-1, MAX_NAME_LENGTH, names, ids);

    printf("The sorted names and IDs are\n");

    for (int i = 0; i < MAX_NAMES; i++) {
        printf("%-20s %d\n", names[i], ids[i]);
    }
    return 0;
}
