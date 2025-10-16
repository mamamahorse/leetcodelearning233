class Solution 
{
public:
    TreeNode* searchBST(TreeNode* root, int val) 
    {
        if (root == NULL || root->val == val) 
        return root; 
        TreeNode* result = NULL;
        if (root->val > val) result = searchBST(root->left, val);
        if (root->val < val) result = searchBST(root->right, val);
        return result;
    }
};

class Solution 
{
public:
    TreeNode* searchBST(TreeNode* root, int val) 
    {
        while (root != NULL) 
        {
            if (root->val > val) 
            root = root->left;
            else if (root->val < val) 
            root = root->right;
            else return root;
        }
        return NULL;
    }
};
//从未有过如此舒服的迭代