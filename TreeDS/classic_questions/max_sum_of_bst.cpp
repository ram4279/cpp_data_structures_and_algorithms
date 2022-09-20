/*
Given a binary tree, find the maximum path sum. The path may start and end at any node in the tree.
Example: 

Input: Root of below tree
       1
      / \
     2   3
Output: 6


See below diagram for another example.
1+2+3

*/

#include <iostream>
#include "mytree.h"

using namespace std;

int max_path_sum_of_bst(Node* root)
{
     int gmax = INT_MIN;
     max_path_sum_of_bst_helper(root, &gmax);
     return gmax;
}

int max_path_sum_of_bst_helper(Node* root, int* gmax)
{
     if (!root) {
          return 0;
     }
     int lh = max_path_sum_of_bst_helper(root->left, gmax);
     int rh = max_path_sum_of_bst_helper(root->right, gmax);

     int straight_max = max((max(lh,rh)+root->data), root->data);
     int gone_through_root_max = max(straight_max, (lh+rh+root->data));
     *gmax = max(gone_through_root_max, *gmax);
     return straight_max;
}