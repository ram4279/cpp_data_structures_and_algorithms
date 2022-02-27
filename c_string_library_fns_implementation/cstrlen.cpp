#include <iostream>

using namespace std;

unsigned int mstrlen(const char* str)
{
    unsigned int len = 0;
    while (*str++) {
        len++;
    }

    return len;
}


int main(int argc, char **argv)
{
    const char *str = "hi";
    cout << "len of " << str << " " <<  mstrlen(str) << endl;

    str = "";
    cout << "len of " << str << " " <<  mstrlen(str) << endl;

    str = "t h a n o s";
    cout << "len of " << str << " " <<  mstrlen(str) << endl;
    
    str = "   darkseid  ";
    cout << "len of " << str << " " <<  mstrlen(str) << endl;

    str = " j 0 k e r ";
    cout << "len of " << str << " " <<  mstrlen(str) << endl;

    return 0;
}
