/*

Sample Output
============

        *   
    *       *   
*               *   
    *       *   
        *   

outerspaces innerspaces
=========== ===========
2           -1
1            1
0            3
1            1
2           -1

*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int n = 0, row = 0, col = 0;
    int outer_spaces = 0; /* spaces outside the diamond rows */
    int inner_spaces = 0; /* spaces inside the diamond rows */
    cin >> n;
    
    outer_spaces = n/2;
    inner_spaces = -1; /* inner spaces will be incremented and decremented by two so initialize to -1 */

    for (row = 0; row < n; row++) {
      
        for (col = 0; col < outer_spaces; col++) {
            cout << "\t";
        }
        cout << "*\t";
        
        for (col = 0; col < inner_spaces; col++) {
            cout << "\t";
        }
        /* The star after inner space should not be printed for first and last row */
        if (row != 0 && row != n-1) {
            cout << "*\t";
        }

        if (row < n/2) {
            outer_spaces -= 1;
            inner_spaces += 2;
        } else {
            outer_spaces += 1;
            inner_spaces -= 2;
        }

        cout << endl;
    }
    return 0;
}
