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

int max_path_sum_of_bst(Node* root);
int max_path_sum_of_bst_helper(Node* root, int* gmax);

bool are_both_tree_same(Node* root1, Node* root2);

void zig_zag_traversal(Node* root);
void cc_boundary_traversal(Node* root);


#endif /* __MYREE__ */