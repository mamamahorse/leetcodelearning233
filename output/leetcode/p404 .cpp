// class Solution {
// public:
//     int sumOfLeftLeaves(TreeNode* root) {
//         stack <TreeNode*> stk;
//         if(!root)
//         return 0;
//         stk.push(root);
//         int sum=0;
//         while(!stk.empty())
//         {
//             TreeNode* node =stk.top();
//             stk.pop();
//             if(node->left!=NULL&&node->left->left==NULL&&node->left->right==NULL)
//             {
//                 sum+=node->left->val;
//             }
//             if(node->right)
//             stk.push(node->right);
//             if(node->left)
//             stk.push(node->left);
//         }
//         return sum;
//     }
// };