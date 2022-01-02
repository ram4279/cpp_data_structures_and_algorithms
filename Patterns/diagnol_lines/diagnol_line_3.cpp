/*

Sample Output
=============

0,0    0,1    0,2    0,3    0,4
1,0    1,1    1,2    1,3    1,4
2,0    2,1    2,2    2,3    2,4
3,0    3,1    3,2    3,3    3,4
4,0    4,1    4,2    4,3    4,4



*               *   
    *       *       
        *           
    *       *       
*               *   

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
        
        for (col = 0; col < n; col++) {
            /* We are combining the logic of diagnol_line_1.cpp and diagnol_line_2.cpp 
             * How middle star is not printed twice, the or logic executes only once.
             */
            if ( row == col || row + col == n-1 ) {
                cout << "*\t";
            } else {
                cout << "\t";
            }
        }
        
        cout << endl;
    }

    return 0;
}
