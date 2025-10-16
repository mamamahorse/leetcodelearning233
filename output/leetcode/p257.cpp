// //递归和回溯是互通的，有一个递归，就要有一个回溯对应
// class Solution 
// {
// private:

//     void traversal(TreeNode* cur, vector<int>& path, vector<string>& result) 
//     {
//         path.push_back(cur->val); // 中
//         if (cur->left == NULL && cur->right == NULL) 
//         {//特殊的终止逻辑 到叶子结点就停止
//             string sPath;
//             for (int i = 0; i < path.size() - 1; i++) 
//             {
//                 sPath += to_string(path[i]);
//                 sPath += "->";
//             }//按要求格式输出
//             sPath += to_string(path[path.size() - 1]);
//             result.push_back(sPath);
//             return;
//         }
//         if (cur->left) 
//         { 
//             traversal(cur->left, path, result);
//             path.pop_back(); // 回溯
//         }
//         if (cur->right) 
//         {
//             traversal(cur->right, path, result);
//             path.pop_back(); // 回溯
//         }
//     }

// public:
//     vector<string> binaryTreePaths(TreeNode* root) 
//     {
//         vector<string> result;
//         vector<int> path;
//         if (root == NULL) return result;
//         traversal(root, path, result);
//         return result;
//     }
// };