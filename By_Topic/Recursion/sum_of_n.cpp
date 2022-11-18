#include <bits/stdc++.h>
using namespace std;

// Summation
void summation(long n, long res)
{
    if (n < 1)  {
        cout << res << endl;
        return;
    }
    summation(n-1, res+n);
}

// Summation with return
long summation_r(long n)
{
    if (n == 0) {
        return 0;
    }
    return n + summation_r(n-1);
}

int main(int argc, char const *argv[])
{
    long n;
    long res = 0;
    cin >> n;
    summation(n, res);
    cout << summation_r(n) << endl;
    return 0;
}
