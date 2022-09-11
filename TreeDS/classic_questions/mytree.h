#ifndef __MYTREE__
#define __MYTREE__
#include <iostream>

struct Node
{
    int data;
    Node* left;
    Node* right;

public:
    /* Constructor */
    Node(int data) {
        this->data  = data;
        this->left  = NULL;
        this->right = NULL; 
    }
};

void one_shot_traversal(Node* root);
void iterative_preorder(Node* root);
void iterative_inorder(Node* root);
void iterative_postorder(Node* root);
void bfs_traversal(Node* root);
Node* insert_into_tree(Node* root, Node* new_node);
int get_height_of_tree(Node* root);
int get_height_of_tree_bfs(Node* root);

int is_bst_helper(Node* root);
bool is_bst_balanced(Node* root);


int diameter_of_tree(Node* root);
int diameter_helper(Node* root, int* diameter);

#endif /* __MYREE__ */