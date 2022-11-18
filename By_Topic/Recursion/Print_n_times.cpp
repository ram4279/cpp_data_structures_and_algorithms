#include <bits/stdc++.h>
using namespace std;

//Print name n times
void print_1_n_name(int count, int limit, const char* name)
{
    if (count > limit) {
        return;
    }
    cout << name << endl;
    print_1_n_name(++count, limit, name);
}


void print_start_to_n_numbers(int count, int limit)
{
    if (count > limit) {
        return;
    }
    cout << count << endl;
    print_start_to_n_numbers(++count, limit);
}


void print_end_to_limit_numbers(int count, int limit)
{
    if (count < limit) {
        return;
    }
    cout << count << endl;
    print_end_to_limit_numbers(--count, limit);
}

// Print 1 to N without the operation +
void print_1_to_n_no_plus(int count, int limit)
{
    if (count < limit) {
        return;
    }
    print_1_to_n_no_plus(count-1, limit);
    cout << count << endl;

}


void print_n_to_1_no_minus(int count, int limit)
{
    if (count > limit) {
        return;
    }
    print_n_to_1_no_minus(count+1, limit);
    cout << count << endl;

}

int main(int argc, char const *argv[])
{
    const char* name_chrs = "lion";
    cout << "print_1_n_name ===========================" << endl;
    print_1_n_name(1,3,name_chrs);
    cout << "print_start_to_n_numbers ===========================" << endl;
    print_start_to_n_numbers(1,3);
    cout << "print_end_to_limit_numbers ===========================" << endl;
    print_end_to_limit_numbers(3,1);
    cout << "print_1_to_n_no_plus ===========================" << endl;
    print_1_to_n_no_plus(3,1);
    cout << "print_1_to_n_no_minus ===========================" << endl;
    print_n_to_1_no_minus(1, 3);
    return 0;
}