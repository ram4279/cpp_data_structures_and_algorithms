#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct wrapper
{
    int x;
    int y;
    char* str;
};

int main(int argc, char const *argv[])
{
    struct wrapper w1, w2;
    w1.x = 10;
    w1.y = 20;
    w1.str = malloc(10);
    strcpy(w1.str, "HOLA AMIGOS");
    printf("w1 = %d %d %s\n", w1.x, w1.y, w1.str);

    w2 = w1;
    w2.x = 100;
    w2.y = 200;
    strcpy(w2.str, "HELLO FRIENDS");
    printf("w2 = %d %d %s\n", w2.x, w2.y, w2.str);

    printf("w1 = %d %d %s\n", w1.x, w1.y, w1.str);
    return 0;
}
