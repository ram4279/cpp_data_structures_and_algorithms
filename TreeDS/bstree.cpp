#include <iostream>
#include <cstddef>
#include <cstring>
#include "bstree.h"

using namespace std;

typedef int (*tree_node_compare_t) (void*, void*);
typedef void (*tree_data_print) (void*);

void t_print_int(void *data)
{
    printf("%d ", *(int *)data);
    return;
}

void initialize_tree(BSTree* tree)
{
    tree->root = NULL;
    tree->node_count = 0;
    return;
}

TreeNode* create_node(void *data, size_t size)
{
    TreeNode* tnode = (TreeNode *)malloc(sizeof(TreeNode));
    tnode->data = malloc(sizeof(size));
    memcpy(tnode->data, data, size);
    tnode->left  = NULL;
    tnode->right = NULL;
    return tnode;
}

TreeNode* get_max(TreeNode* root) {
    while (root->right) {
        root=root->right;
    }
    return root;
}

TreeNode* delete_from_tree(TreeNode* root, TreeNode* delete_node, tree_node_compare_t compare)
{
    if (compare(delete_node->data, root->data) > 0) {
        root->right = delete_from_tree(root->right, delete_node, compare);
    } else if (compare(delete_node->data, root->data) < 0) {
        root->left = delete_from_tree(root->left, delete_node, compare);
    } else {
        if (root->left && root->right) {
            TreeNode* max = get_max(root->left);
            memcpy(root->data, max->data, sizeof(max->data));
            root->left = delete_from_tree(root->left, max, compare);
            return root;
        } else if (root->left) {
            delete root;
            return root->left;
        } else if (root->right) {
            delete root;
            return root->right;
        } else {
            delete root;
            return NULL;
        }

    }

    return root;

}

TreeNode* insert_into_tree(BSTree *tree, TreeNode* new_node, tree_node_compare_t compare)
{
    TreeNode* parent = NULL;
    TreeNode* cur    = NULL;
    
    if (!tree->root) {
        tree->node_count += 1;
        tree->root = new_node;
        return tree->root;
    }

    cur = tree->root;
    while(cur) {
        parent = cur;
        if (compare(new_node->data, cur->data) > 0) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }

    if (compare(parent->data, new_node->data) > 0) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    tree->node_count += 1;
    return tree->root;

}


TreeNode* insert_into_tree_r(BSTree* tree, TreeNode* root, TreeNode* new_node, tree_node_compare_t compare)
{
    if (!root) {
        return new_node;
    }

    if (compare(new_node->data, root->data) > 0) {
        root->right = insert_into_tree_r(tree, root->right, new_node, compare);
    } else {
        root->left = insert_into_tree_r(tree, root->left, new_node, compare);
    }

    return root;
}


int compare_int(void *data1, void *data2) 
{
    int d1 = *(int *)data1;
    int d2 = *(int *)data2;
    int res;

    if (d1 < d2) {
        res = -1;
    } else if (d1 > d2) {
        res = 1;
    } else {
        res = 0;
    }

    cout << "Comparing " << d1 << " with " << d2 << " returns " << res << endl;
    return res;
}

void preorder_traversal(TreeNode* root, tree_data_print t_print_int)
{
    if (root == NULL) {
        return;
    }
    t_print_int(root->data);
    preorder_traversal(root->left, t_print_int);
    preorder_traversal(root->right, t_print_int);
}


void postorder_traversal(TreeNode* root, tree_data_print t_print_int)
{
    if (root == NULL) {
        return;
    }
    postorder_traversal(root->left, t_print_int);
    postorder_traversal(root->right, t_print_int);
    t_print_int(root->data);
}

void inorder_traversal(TreeNode* root, tree_data_print t_print_int)
{
    if (root == NULL) {
        return;
    }
    inorder_traversal(root->left, t_print_int);
    t_print_int(root->data);
    inorder_traversal(root->right, t_print_int);
}



int main()
{
    BSTree mytree; 
    initialize_tree(&mytree);

    int arr[] = {4,3,1,9,5,6,7,11,2};
    int len = sizeof(arr)/sizeof(arr[0]);

    for (int i = 0; i < len; i++) {
        TreeNode* new_node = create_node(&arr[i], sizeof(int));
        //Iterative insertion
        //insert_into_tree(&mytree, new_node, compare_int);    

        //Recursive insertion
        mytree.root = insert_into_tree_r(&mytree, mytree.root, new_node, compare_int);
        if (mytree.root != NULL) {
            mytree.node_count += 1;
        }
    }

    cout << "preorder_traversal" << endl;
    preorder_traversal(mytree.root, t_print_int);
    cout << endl;

    cout << "inorder_traversal" << endl;
    inorder_traversal(mytree.root, t_print_int);
    cout << endl;

    cout << "postorder_traversal" << endl;
    postorder_traversal(mytree.root, t_print_int);
    cout << endl;
    cout << "Total nodes inserted = " << mytree.node_count << endl;

    int x = 2;
    TreeNode* delete_node = create_node(&x, sizeof(int));
    mytree.root = delete_from_tree(mytree.root, delete_node, compare_int);

    x = 9;
    delete_node = create_node(&x, sizeof(int));
    mytree.root = delete_from_tree(mytree.root, delete_node, compare_int);


    cout << "preorder_traversal" << endl;
    preorder_traversal(mytree.root, t_print_int);
    cout << endl;
    return 0;
}
