// class Solution {
// public:
//     TreeNode* insertIntoBST(TreeNode* root, int val) 
//     {
//         if (root == NULL) 
//         {
//             TreeNode* node = new TreeNode(val);
//             return node;
//         }
//         if (root->val > val) 
//         root->left = insertIntoBST(root->left, val);
//         if (root->val < val) 
//         root->right = insertIntoBST(root->right, val);
//         return root;
//     }
// };
// class Solution {
// public:
//     TreeNode* insertIntoBST(TreeNode* root, int val) 
//     {   if (root==NULL)
//         {
//             TreeNode* node = new TreeNode(val);
//             return node;
//         }
//         TreeNode*cur=root;
//         TreeNode *pre=NULL;
//         while(cur)
//         {
//             pre=cur;
//             if(cur->val>val)
//             {
//                 cur=cur->left;
//             }
//             else
//             {
//                 cur=cur->right;
//             }
//         }
//         TreeNode * node =new TreeNode(val);
//         if(pre->val>val)
//         {
//             pre->left=node;
//         }
//         else
//         {
//             pre->right=node;
//         }
//         return root;
        
//     }
// };