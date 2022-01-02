/*

Output:
======

*   *   *       *   *   *   
*   *               *   *   
*                       *   
*   *               *   *   
*   *   *       *   *   *   

*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int n = 0, spaces = 0, stars = 0;
    int row = 0, space = 0, star = 0;
    cin >> n;
    stars  = n/2 + 1;
    spaces = 1;
    
    for (row = 0; row < n; row++) {
        
        for (star = 0; star < stars; star++) {
            cout << "*\t";
        }
        
        for (space = 0; space < spaces; space++) {
            cout << "\t";
        }

        for (star = 0; star < stars; star++) {
            cout << "*\t";
        }
        
        if (row < n/2) {
            stars  -= 1;
            spaces += 2;
        } else {
            stars  += 1;
            spaces -= 2;
        }
        cout << endl;
    }
    return 0;
}
