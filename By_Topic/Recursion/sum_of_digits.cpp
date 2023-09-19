#include <iostream>

using namespace std;

int sum_of_digits(int num)
{
    if (num == 0) {
        return 0;
    }

    int smaller_output = sum_of_digits(num/10);
    return smaller_output + (num % 10);
}


int main(int argc, char const *argv[])
{
    cout << sum_of_digits(1000) << endl;
    cout << sum_of_digits(44444) << endl;
    cout << sum_of_digits(444) << endl;
    return 0;
}
