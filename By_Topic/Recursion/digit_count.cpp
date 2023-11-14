#include <iostream>

using namespace std;

int digit_count(int num)
{
    if (num == 0) {
        return 0;
    }

    int smaller_output = digit_count(num/10);
    return smaller_output + 1;
}


int main(int argc, char const *argv[])
{
    cout << digit_count(1000) << endl;
    cout << digit_count(44444) << endl;
    cout << digit_count(444) << endl;
    return 0;
}
