#include <iostream>
#include <cassert>

#define BUFF_SIZE 128

using namespace std;

char* mstrcpy(char* dst, const char* src)
{
    assert(dst != NULL && src != NULL);
    char *temp = dst; 
    while (*dst++ = *src++);
    return temp;
}


/* above code in verbose mode */
#if 0

char* mstrcpy(char* dst, const char* src)
{
    assert(dst != NULL && src != NULL);
    char *temp = dst; 
    while (*src) {
        *dst = *src;
        dst++;
        src++;
    }
    return temp;
}

#endif


int main(int argc, char **argv)
{
    const char *str = "batman";
    char buffer[BUFF_SIZE] = { 0 };

    mstrcpy(buffer, str);
    cout << "str = " << str << " buffer value = " << buffer << endl;

    str = "spiderman";
    mstrcpy(buffer, str);
    cout << "str = " << str << " buffer value = " << buffer << endl;

    str = "";
    mstrcpy(buffer, str);
    cout << "str = " << str << " buffer value = " << buffer << endl;

    str = "scarlett witch and vision";
    cout << "str = " << str << " buffer value = " << mstrcpy(buffer, str) << endl;

    return 0;
}

