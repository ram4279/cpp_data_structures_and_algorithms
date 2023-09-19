#include <iostream>
using namespace std;

void print_reverse(char* name, int idx)
{
    if (name[idx] == '\0')
    {
        return;
    }
    print_reverse(name, idx + 1);
    cout << name[idx];
}



int main(int argc, char const *argv[])
{
    char name[] = "sairamkamalay";
    print_reverse(name, 0);
    cout << endl;
    return 0;
}
