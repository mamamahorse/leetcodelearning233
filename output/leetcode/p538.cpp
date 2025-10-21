// class Solution
// {private:
//     int pre =0;
//     void traversal(TreeNode *cur)
//     {
//         if(cur==NULL)
//         return;
//         traversal(cur->right);
//         cur->val+=pre;
//         pre=cur->val;
//         traversal(cur->left);
//     }
//     public:
//     TreeNode* convertBST(TreeNode* root) 
//     {
//         traversal(root);
//         return root;
//     }

// };