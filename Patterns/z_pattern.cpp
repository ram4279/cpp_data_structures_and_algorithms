#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        if (i == 0 || i == n-1) {
            cout << string(n, '*') << endl;
        } else {
            cout << string(n - i - 1, ' ');
            cout << "*" << endl;
        }
    }
    return 0;
}
