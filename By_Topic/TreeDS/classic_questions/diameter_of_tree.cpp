#include <iostream>
#include "mytree.h"
using namespace std;

int diameter_of_tree(Node* root)
{
    int diameter = 0;
    diameter_helper(root, &diameter);
    return diameter;
}


int diameter_helper(Node* root, int* diameter)
{
    if (!root) {
        return 0;
    }
    int lh = diameter_helper(root->left, diameter);
    int rh = diameter_helper(root->right, diameter);

    *diameter = max(*diameter, lh+rh);
    return 1+max(lh,rh);
}