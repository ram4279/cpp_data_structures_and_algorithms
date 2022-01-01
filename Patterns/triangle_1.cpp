/*

Output:
======
    *
    **
    ***
    ****
    *****

*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int n = 0;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cout << string(i+1, '*') << endl;
    }

    return 0;
}
