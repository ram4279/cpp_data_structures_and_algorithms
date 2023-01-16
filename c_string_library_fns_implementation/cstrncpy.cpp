#include <iostream>
#include <cstring>
#include <cassert>

#define BUFF_SIZE 128

using namespace std;

char* mstrncpy(char *dst, const char *src, size_t len)
{
    assert(dst != NULL && src != NULL);
    char *temp = dst;
    while (len-- && (*dst++ = *src++));
    return temp;
}

char* mstrncpy2(char *dst, const char *src, size_t len)
{
    assert(dst != NULL && src != NULL);
    char *temp = dst;
    for (int i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    return temp;
}

int main(int argc, char **argv)
{
    const char *str = "batman";
    char buffer[BUFF_SIZE] = { 0 };
    
     mstrncpy(buffer, str, strlen(str));
     cout << "str = " << str << " buffer value = " << buffer << endl;

    str = "spiderman";
    mstrncpy(buffer, str, strlen(str));
    cout << "str = " << str << " buffer value = " << buffer << endl;

    str = "";
    mstrncpy(buffer, str, strlen(str));
    cout << "str = " << str << " buffer value = " << buffer << endl;

    str = "scarlett witch and vision";
    cout << "str = " << str << " buffer value = " << mstrncpy2(buffer, str, strlen(str))<< endl;


     return 0;
}
