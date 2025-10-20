// //如果不是bst，则需要遍历。
// class Solution {
// private:

// void searchBST(TreeNode* cur, unordered_map<int, int>& map) 
// { // 前序遍历
//     if (cur == NULL) return ;
//     map[cur->val]++; // 统计元素频率
//     searchBST(cur->left, map);
//     searchBST(cur->right, map);
//     return ;
// }
// bool static cmp (const pair<int, int>& a, const pair<int, int>& b) 
// {
//     return a.second > b.second;
// }
// public:
//     vector<int> findMode(TreeNode* root) 
//     {
//         unordered_map<int, int> map; // key:元素，value:出现频率
//         vector<int> result;
//         if (root == NULL) return result;
//         searchBST(root, map);
//         vector<pair<int, int>> vec(map.begin(), map.end());//可以像这样把map变为vector！
//         sort(vec.begin(), vec.end(), cmp);
//         result.push_back(vec[0].first);
//         for (int i = 1; i < vec.size(); i++) 
//         {
//             if (vec[i].second == vec[0].second) //注意可能有多个最高频率
//             result.push_back(vec[i].first);
//             else break;
//         }
//         return result;
//     }
// };

// class Solution {
// private:
//     int maxCount = 0; 
//     int count = 0; 
//     TreeNode* pre = NULL;
//     vector<int> result;
//     void searchBST(TreeNode* cur) 
//     {
//         if (cur == NULL) return ;

//         searchBST(cur->left);       // 左
//             // 中
//         if (pre == NULL) 
//         { // 第一个节点
//             count = 1;
//         } 
//         else if (pre->val == cur->val) 
//         { // 与前一个节点数值相同
//             count++;
//         } 
//         else 
//         { // 与前一个节点数值不同
//             count = 1;
//         }
//         pre = cur; // 更新上一个节点

//         if (count == maxCount) { // 如果和最大值相同，放进result中
//             result.push_back(cur->val);
//         }

//         if (count > maxCount) { // 如果计数大于最大值频率
//             maxCount = count;   // 更新最大频率
//             result.clear();     // 很关键的一步，不要忘记清空result，之前result里的元素都失效了
//             result.push_back(cur->val);
//         }

//         searchBST(cur->right);      // 右
//         return ;
//     }

// public:
//     vector<int> findMode(TreeNode* root) 
//     {
//         count = 0;
//         maxCount = 0;
//         pre = NULL; // 记录前一个节点
//         result.clear();

//         searchBST(root);
//         return result;
//     }
// };
// class Solution 
// {
// public:
//     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
//     {
//         if (root == q || root == p || root == NULL) 
//         return root;
//         TreeNode* left = lowestCommonAncestor(root->left, p, q);
//         TreeNode* right = lowestCommonAncestor(root->right, p, q);
//         if (left != NULL && right != NULL) 
//         return root;
//         if (left == NULL) 
//         return right;
//         return left;
//     }
// };