// class Solution 
// {
// public:
//     int getMinimumDifference(TreeNode* root) 
//     { stack<TreeNode*> st;
//         TreeNode* cur=root;
//         TreeNode* pre=nullptr;
//         int res=INT_MAX;
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
//                 if(pre)
//                     res=min(res,cur->val-pre->val);
//                 pre=cur;
//                 cur=cur->right;
//             }
//         }
//         return res;
        
//     }
// }; 
// 迭代写法。
