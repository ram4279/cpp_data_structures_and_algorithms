#include <iostream>
#include "mytree.h"

bool are_both_tree_same(Node* root1, Node* root2)
{
    if (!root1 || !root2) {
        return root1 == root2;
    }

    if (root1->data != root2->data) {
        return false;
    }

    return are_both_tree_same(root1->left, root2->left) &&
           are_both_tree_same(root1->right, root2->right);
}