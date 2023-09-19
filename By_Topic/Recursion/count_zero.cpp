#include <iostream>

using namespace std;

int count_zeros(int n)
{
    if (n == 0) return 0;
    int smaller_res = count_zeros(n/10);
    return smaller_res + (n % 10 == 0 ? 1: 0);
}


int main(int argc, char const *argv[])
{
    cout << count_zeros(1023000) << endl;
    cout << count_zeros(101010) << endl;
    cout << count_zeros(110110) << endl;
    return 0;
}
