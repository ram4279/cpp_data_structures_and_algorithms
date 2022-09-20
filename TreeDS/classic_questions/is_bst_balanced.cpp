/*
A height balanced binary tree is a binary tree in which the height of the left subtree and right subtree of any node 
does not differ by more than 1 
and both the left and right subtree are also height balanced.

Height balanced
       1
      / \
    2    4
   /
  3

Not Height balanced
    1
   / \
  2   5
   \
    3
   /
  4

*/
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
