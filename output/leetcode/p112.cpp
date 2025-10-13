// class Solution {
// private:
//     bool traversal(TreeNode* cur, int count) 
//     {
//         if (!cur->left && !cur->right && count == 0) 
//         return true;
//         if (!cur->left && !cur->right) 
//         return false;

//         if (cur->left) 
//         { // 左
//             count -= cur->left->val; // 递归，处理节点;
//             if (traversal(cur->left, count)) 
//             return true;
//             count += cur->left->val; // 回溯，撤销处理结果
//         }
//         if (cur->right) { // 右
//             count -= cur->right->val; // 递归，处理节点;
//             if (traversal(cur->right, count)) 
//             return true; 
//             count += cur->right->val; // 回溯，撤销处理结果
//         }
//         return false;
//     }

// public:
//     bool hasPathSum(TreeNode* root, int sum) 
//     {
//         if (root == NULL) return false;
//         return traversal(root, sum - root->val);
//     }
// };
// class Solution 
// {
// public:
//     bool hasPathSum(TreeNode* root, int targetSum) 
//     {
    
//         if (root == NULL) 
//         return false;

//         if (root->left == NULL && root->right == NULL)
//             return root->val == targetSum;

//         return hasPathSum(root->left, targetSum - root->val) ||
//                hasPathSum(root->right, targetSum - root->val);
//     }
// };