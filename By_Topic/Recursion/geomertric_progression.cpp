#include <iostream>
#include <cmath>

using namespace std;

double gp(int n)
{
    if (n == 0) return 1;
    double smaller_res = gp(n -1);
    return smaller_res + (1.0/pow(2, n));
}


int main(int argc, char const *argv[])
{
    cout << gp(10) << endl;
    cout << gp(15) << endl;
    cout << gp(3) << endl;
    return 0;
}
