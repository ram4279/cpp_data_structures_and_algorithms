#include <iostream>
#include <cstring>
#include <cassert>

#define BUFF_SIZE 128

using namespace std;

char* mstrcat(char *dst, const char *src)
{
    assert(dst != NULL && src != NULL);
    char *temp = dst;
    dst = dst + strlen(dst);
    while(*dst++ = *src++);
    return temp;
}

int main(int argc, char **argv)
{
    char buffer[BUFF_SIZE]  = {0};
    
    strcpy(buffer, "Batman vs ");
    mstrcat(buffer, "Superman");

    cout << buffer << endl;
    
    memset(buffer, 0, sizeof(buffer));

    strcpy(buffer, "Avengers");
    mstrcat(buffer, " age of");
    mstrcat(buffer, " Ultron");

    cout << buffer << endl;
    return 0;
}


