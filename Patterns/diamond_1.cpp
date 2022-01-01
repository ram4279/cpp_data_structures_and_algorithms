/*

Output:
=======

        *   
    *   *   *   
*   *   *   *   *   
    *   *   *   
        *   

*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int n = 0, spaces = 0, stars = 0;
    int row = 0, space = 0, star = 0;
    cin >> n;

    /* A new techinque of using variables to hold the numbers of stars and spaces to be printed
     * is used here. We start with initializing the spaces and stars variable.
     */
    spaces = n / 2;
    stars = 1;

    /* Outer most loop controls the number of rows */
    for (row = 0; row < n; row++) {
        
        for (space = 0; space < spaces; space++) {
            cout << "\t";
        }

        for (star = 0; star < stars; star++) {
            cout << "*\t";
        }
        
        /* Before middle of the diamond keep on decreasing the spaces and increase the stars */
        if (row < n/2) {
            spaces--;
            stars += 2;
        } 
        /* After reaching middle and next keep increasing the spaces and decrease the stars */
        else {
            spaces++;
            stars -= 2;
        }
        cout << endl;
    }
    
    return 0;
}
