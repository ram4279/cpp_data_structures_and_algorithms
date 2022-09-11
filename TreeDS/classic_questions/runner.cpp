#include <iostream>
#include "mytree.h"

using namespace std;

int main()
{
    Node* root = NULL;
    int arr[] = {3,7,1,2,6,5,9,4};
    int len = sizeof(arr)/sizeof(arr[0]);

    for (int i = 0; i < len; i++) {
        Node* new_node = new Node(arr[i]);
        root = insert_into_tree(root, new_node);
    }
    cout << endl;

    cout << "Preorder " << endl;
    iterative_preorder(root);
    cout << "Inorder" << endl;
    iterative_inorder(root);
    cout << "Postorder " << endl;
    iterative_postorder(root);
    cout << "BFS " << endl;
    bfs_traversal(root);

    cout << "One shot traversal" << endl;
    one_shot_traversal(root);

    int height_of_tree = -1;
    height_of_tree = get_height_of_tree(root);
    cout << "Height of tree = " << height_of_tree << endl;

    height_of_tree = get_height_of_tree_bfs(root);
    cout << "Height of tree bfs = " << height_of_tree << endl;

    cout << "Is tree balanced = " << is_bst_balanced(root) << endl;

    cout << "diameter of BST = " << diameter_of_tree(root) << endl;

    return 0;
}
