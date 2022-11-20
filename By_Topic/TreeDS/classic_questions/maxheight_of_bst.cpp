#include <iostream>
#include <stack>
#include <queue>
#include "mytree.h"
using namespace std;


int get_height_of_tree(Node* root)
{
    if (!root) {
        return 0;
    }
    int lh = get_height_of_tree(root->left);
    int rh = get_height_of_tree(root->right);
    return max(lh, rh) + 1;
}

int get_height_of_tree_bfs(Node* root) {
    queue<Node*> q;
    Node* cur_node = NULL;
    if (!root) {
        return -1;
    }
    int height = 0;
    int cur_level_node_count = 0;
    q.push(root);
    while (!q.empty()) {
        height++;
        cur_level_node_count = q.size();
        while (cur_level_node_count--)
        {
            cur_node = q.front();
            q.pop();

            if (cur_node->left) {
                q.push(cur_node->left);
            }

            if (cur_node->right) {
                q.push(cur_node->right);
            }
        }   
    }
    return height;
}