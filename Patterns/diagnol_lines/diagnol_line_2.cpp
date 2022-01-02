/*

Sample Output
=============

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
    int n = 0;
    int row = 0, col = 0;
    cin >> n;

    for (row = 0; row < n; row++) {
        
        for (col = 0; col < n; col++) {
            /* From the op we can see that if sum of row and col equals to n-1 we have to print star
             * ie (0+4 = 4), (1+3 = 4) and so on.
             */
            if (row + col == n - 1) {
                cout << "*";
            } else {
                cout << "\t";
            }
        }

        cout << endl;
    }
    
    return 0; 

}
