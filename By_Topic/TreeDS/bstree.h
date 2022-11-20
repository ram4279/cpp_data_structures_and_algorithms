#ifndef  __MYBSTREE__
#define  __MYBSTREE__

struct TreeNode
{
    void *data;
    TreeNode* left;  
    TreeNode* right;  
};

struct BSTree
{
    TreeNode* root;
    int node_count;
};

#endif // __MYBSTREE__
