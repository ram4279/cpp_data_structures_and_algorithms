#include <iostream>
#include <string>
#include "hash_table.h"

int main(int argc, char const *argv[])
{
    Hashtable<int> table;
    table.insert("mango", 122);
    table.insert("orange", 41);
    table.insert("kiwi", 13);
    table.insert("lalliga", 21);
    table.insert("trello", 12);
    table.insert("orenge", 41);
    table.insert("kiwei", 13);
    table.insert("liga", 21);
    table["epl"] = 200;
    table.print();

    while (true) {
        string fruit;
        cin >> fruit;
        table.erase(fruit);
        table.print();
    }

    return 0;
}
