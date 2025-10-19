// class Solution {
// public:
//     bool isValidBST(TreeNode* root) 
//     { stack<TreeNode*> st;
//         TreeNode* cur=root;
//         TreeNode* pre=nullptr;
//         while(cur||!st.empty())
//         {
//             if(cur)
//             {
//                 st.push(cur);
//                 cur=cur->left;
//             }
//             else
//             {
//                 cur=st.top();
//                 st.pop();
//                 if(pre&&cur->val<=pre->val)
//                     return false;
//                     pre=cur;
//                     cur=cur->right;
//             }
//         }
//         //迭代模拟递归，左中右，先到最左，再回溯。
//         return true;
//     }
// };