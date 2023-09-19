#include <iostream>
using namespace std;

void remove_char(char* str, char c)
{
    if (str[0] == '\0') {
        return;
    }

    if (str[0] != c) {
        remove_char(str + 1, c);
    } else {
        for (int i = 0; str[i]; i++) {
            str[i] = str[i+1];
        }
        remove_char(str, c);
    }
}

int main(int argc, char const *argv[])
{
    char name[256];
    cin >> name;
    remove_char(name, 'a');
    cout << name;
    return 0;
}
