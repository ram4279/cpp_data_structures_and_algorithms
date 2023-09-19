#include <iostream>
#include <string>
using namespace std;

void print_subseq(char *input, char *output, size_t i)
{
    if (input[0] == '\0') {
        output[i] = '\0';
        cout << output << endl;
        return;
    }
    output[i] = input[0];
    print_subseq(input + 1, output, i + 1);
    print_subseq(input + 1, output, i);
}


void print_subseq2(string input, string output)
{
    if (input.size() == 0) {
        cout << output << endl;
        return;
    }
    print_subseq2(input.substr(1), output + input[0]);
    print_subseq2(input.substr(1), output);
}

int main(int argc, char const *argv[])
{
    char input[100];
    char output[100];
    string ip, op;
    cin >> ip;
    print_subseq2(ip, op);
    return 0;
}
