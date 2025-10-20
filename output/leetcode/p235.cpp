// class Solution 
// {
// public:
//     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
//     {
//         if (root->val > p->val && root->val > q->val) 
//           return lowestCommonAncestor(root->left, p, q);
//         else if (root->val < p->val && root->val < q->val) 
//             return lowestCommonAncestor(root->right, p, q);
//          return root;
//          //在这样的逻辑中，左子树一路走到底，如果找到，就直接返回
//          //如此，便可以节约时间，有赖于bst的有序性
//     }
// };
// class Solution 
// {
// public:
//     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
//     {
//         while(root) 
//         {
//             if (root->val > p->val && root->val > q->val) 
//             {
//                 root = root->left;
//             } 
//             else if (root->val < p->val && root->val < q->val) 
//             {
//                 root = root->right;
//             } 
//             else return root;
//         }
//         return NULL;
//     }
// };