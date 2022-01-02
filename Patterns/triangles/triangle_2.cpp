/*

Output:
=======
*   *   *   *   *   
*   *   *   *   
*   *   *   
*   *   
*


*/
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int n = 0;
    cin >> n;

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= i; j++) {
            cout << "*\t";
        }
        cout << "\n";
    }
    return 0;
}
