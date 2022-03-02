#include <stdio.h>

enum
{
    KAKASHI = 2,
    NARUTO = 0,
    PAIN = 3,
    TOBI = 4,
    JIRAYA = 1
};


int main()
{
    char names[][20] = {
                          [NARUTO]  = "KAKASHI",
                          [KAKASHI] = "NARUTO",
                          [TOBI]    = "PAIN",
                          [PAIN]    = "TOBI",
                          [JIRAYA]  = "JIRAYA"
                       };

    int no = sizeof(names)/sizeof(names[0]);
    for (int i = 0; i < no; i++) {
        printf("%d: -> %s\n", i, names[i]);
    }

    return 0;
}

/*
* OP:
0: -> KAKASHI
1: -> JIRAYA
2: -> NARUTO
3: -> TOBI
4: -> PAIN
*/
