#include <iostream>
using namespace std;

void remove_duplicates(char* str)
{
    if (str[0] == '\0') {
        return;
    }

    if (str[0] != str[1]) {
        remove_duplicates(str + 1);
    } else {
        for (int i = 0; str[i]; i++) {
            str[i] = str[i+1];
        }
        remove_duplicates(str);
    }
}

int main(int argc, char const *argv[])
{
    char name[256];
    cin >> name;
    remove_duplicates(name);
    cout << name << endl;
    return 0;
}
