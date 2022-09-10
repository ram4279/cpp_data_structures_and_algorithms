#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include "mytree.h"

using namespace std;

Node* insert_into_tree(Node* root, Node* new_node)
{
    if (!root) {
        /* Location found return the node it will attach to the leaf node */
        root = new_node;
        return root;
    } else {
        /* If data is less than or equal to curr data go left else go right*/
        if (new_node->data <= root->data) {
            root->left = insert_into_tree(root->left, new_node);
        } else {
            root->right = insert_into_tree(root->right, new_node);
        }
    }
    return root;
}


void one_shot_traversal(Node* root)
{
    stack<pair<Node*,int>> stk;
    vector<Node*> preorder, postorder, inorder;
    if (!root) {
        return;
    }

    auto root_pair = make_pair(root, 1);
    stk.push(root_pair);
    while (!stk.empty())
    {
        auto cur_node = stk.top();
        stk.pop();
        if (cur_node.second == 1) {
            preorder.push_back(cur_node.first);
            cur_node.second+=1;
            stk.push(cur_node);
            if (cur_node.first->left) {
                auto new_pair = make_pair(cur_node.first->left, 1);
                stk.push(new_pair);
            }
        } else if (cur_node.second == 2) {
            inorder.push_back(cur_node.first);
            cur_node.second+=1;
            stk.push(cur_node);
            if (cur_node.first->right) {
                auto new_pair = make_pair(cur_node.first->right, 1);
                stk.push(new_pair);
            }
        } else {
            postorder.push_back(cur_node.first);
        }
    }
    for (auto elem : preorder) {
        cout << elem->data << " ";
    }
    cout << endl;
    for (auto elem : inorder) {
        cout << elem->data << " ";
    }
    cout << endl;
    for (auto elem : postorder) {
        cout << elem->data << " ";
    }
    cout << endl;
}

void iterative_preorder(Node* root)
{
    if (!root) {
        return;
    }
    stack<Node*> stk;
    stk.push(root);
    Node* cur = stk.top();
    while (!stk.empty()) {
        cur = stk.top();
        stk.pop();
        cout << cur->data << " ";
        if (cur->right) {
            stk.push(cur->right);
        }
        if (cur->left) {
            stk.push(cur->left);
        }
    }
    cout << endl;
    
}

void iterative_inorder(Node* root)
{
    if (!root) {
        return;
    }
    stack<Node*> stk;
    while (true) {
        if (root) {
            /* Keep on pushing to the stack until root->left is not NULL */
            stk.push(root);
            root = root->left;
        } else {
            if (stk.empty()) {
                break;
            }
            root = stk.top();
            /* Let subtree traversal completed now print root and go to right */
            cout << root->data << " ";
            stk.pop();
            root = root->right;
        }
    }
    cout << endl;
}

void iterative_postorder(Node* root)
{
    if (!root) {
        return;
    }
    Node* temp      = NULL;
    stack<Node*> stk;
    while (root || !stk.empty()) {
        if (root) {
            stk.push(root);
            root = root->left;
        } else {
            temp = stk.top()->right;
            if (!temp) {
                /* At this moment we are at leaf node, as leaf is the only node
                 * which has no left and right
                 */
                temp = stk.top();
                cout << temp->data << " ";
                stk.pop();
                /* Time for stack unwinding */
                while (!stk.empty() && stk.top()->right == temp)
                {
                    temp = stk.top();
                    stk.pop();
                    cout << temp->data << " ";
                }
            } else {
                root = temp;
            }
        }
    }
    cout << endl;
    return;
}

/**
 * @brief bfs_traversal
 * @param root 
 * 
 * @detail Use queue DS to travere in bfs
 * 
 */
void bfs_traversal(Node* root)
{
    if (!root) {
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->left) {
            q.push(curr->left);
        }
        if (curr->right) {
            q.push(curr->right);
        }
    }
    cout << endl;
    return;
}