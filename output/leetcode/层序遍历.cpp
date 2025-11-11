// class Solution {
// public:
//     vector<vector<int>> levelOrder(TreeNode* root) 
//     {
//         queue<TreeNode*> que;
//         if (root != NULL) 
//         que.push(root);
//         vector<vector<int>> result;
//         while (!que.empty()) 
//         {
//             int size = que.size();
//             vector<int> vec;
//             for (int i = 0; i < size; i++) {
//                 TreeNode* node = que.front();
//                 que.pop();
//                 vec.push_back(node->val);
//                 if (node->left) que.push(node->left);
//                 if (node->right) que.push(node->right);
//             }
//             result.push_back(vec);
//         }
//         return result;
//     }
// };
// // 用递归写
// class Solution
// {
//     public:
//     void order(TreeNode* cur,vector<vector<int>>& result, int depth)
//     {
//         if(cur==nullptr)
//         return;
//         if(result.size()==depth)
//         result.push_back(vector<int>());
//         result[depth].push_back(cur->val);
//         order(cur->left,result,depth+1);
//         order(cur->right,result,depth+1);
//     }
//       vector<vector<int>> levelOrder(TreeNode* root) 
//     {
//         vector<vector<int>> result;
//         int depth = 0;
//         order(root, result, depth);
//         return result;
//     }
// };