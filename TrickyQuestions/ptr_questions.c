#include <stdio.h>

int main(int argc, char const *argv[])
{
    char* str = "THIS IS A STRING";
    char* p = str;
    p++; // Now p is at HIS IS A STRING
    printf("%s\n",p);
    *p++; // Now p is at I
    printf("%c\n", *p);
    *++p; // Same precedence no issue; p is at S
    printf("%c\n", *p);
    ++*p; // Runtime Error trying to modify read only memory
    return 0;
}
