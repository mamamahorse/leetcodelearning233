// class Solution {
// public:
//     int sumOfLeftLeaves(TreeNode* root) 
//     { if(root==NULL)
//         return 0;
//         if(root->left==NULL&&root->right==NULL)
//             return 0;
//         int leftvalue=sumOfLeftLeaves(root->left);
//         if(root->left!=NULL&&root->left->left==NULL&&root->left->right==NULL)
//             leftvalue+=root->left->val;
//         int rightvalue=sumOfLeftLeaves(root->right);
//         return leftvalue+rightvalue; 
//     }
// };
// class Solution 
// {
// public:
//     int sumOfLeftLeaves(TreeNode* root) 
//     {
//         if (root == NULL) return 0;
//         int leftValue = 0;
//         if (root->left != NULL && root->left->left == NULL && root->left->right == NULL) {
//             leftValue = root->left->val;
//         }
//         return leftValue + sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
//     }
// };