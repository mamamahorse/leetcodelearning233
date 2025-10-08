// class Solution 
// {
// public:
//     vector<int> largestValues(TreeNode* root) 
//     {  
//         queue<TreeNode*> que;
//         if (root != NULL) que.push(root);
//         vector<int> result;
//         while (!que.empty()) 
//         {
//             int size = que.size();
//             int maxVal = INT_MIN; // 每一层的最大值
//             for (int i = 0; i < size; i++) 
//             {
//                 TreeNode* node = que.front();
//                 que.pop();
//                 if (node->val > maxVal) maxVal = node->val;
//                 if (node->left) que.push(node->left);
//                 if (node->right) que.push(node->right);
//             }
//             result.push_back(maxVal);
//         }
//         return result;
        
//     }
// };