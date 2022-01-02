/*

Output:
=======

*  
    *   
        *   
            *   
                *   

*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int n = 0, row = 0;
    int col = 0;
    cin >> n;
    
    for (row = 0; row < n; row++) {

        for (col = 0; col < row + 1; col++) {
            /* From the op we can see that if row and column are same we have to print star 
             * ie (0,0) (1,1) (2,2) and so on.
             */
            if (row == col) {
                cout << "*";
            } else {
                cout << "\t";
            }
        }
        cout << endl;
    }
    return 0;
}
