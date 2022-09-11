#include <iostream>
#include "mytree.h"

using namespace std;


int is_bst_helper(Node* root)
{
    if (!root) {
        return 0;
    }
    int lh = is_bst_helper(root->left);
    int rh = is_bst_helper(root->right);

    if (lh == -1 || rh == -1) {
        return -1;
    }

    if (abs(lh - rh) > 1) {
        return -1;
    }

    return 1 + max(lh, rh);
}



bool is_bst_balanced(Node* root)
{
    if (!root) {
        return false;
    }
    
    return is_bst_helper(root) == -1 ? false : true;
}
