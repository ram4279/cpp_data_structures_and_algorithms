#include <iostream>

using namespace std;

//5, 3
int mul(int m, int n)
{
    if (n == 0) {
        return 0;
    }
    int smaller_res = mul(m, n-1);
    return smaller_res + m;
}


int main(int argc, char const *argv[])
{
    cout << mul(3,4) << endl;
    cout << mul(33,10) << endl;
    cout << mul(11,11) << endl;
    return 0;
}
