// class Solution {
// public:
//     long long maxVal = LONG_MIN; // 因为后台测试数据中有int最小值
//     bool isValidBST(TreeNode* root) 
//     {
//         if (root == NULL) return true;

//         bool left = isValidBST(root->left);
//         // 中序遍历，验证遍历的元素是不是从小到大
//         if (maxVal < root->val)
//          maxVal = root->val;
//         else 
//         return false;
//         bool right = isValidBST(root->right);

//         return left && right;
//     }
// };
// class Solution {
// private:
//     vector<int> vec;
//     void traversal(TreeNode* root) {
//         if (root == NULL) return;
//         traversal(root->left);
//         vec.push_back(root->val); // 将二叉搜索树转换为有序数组
//         traversal(root->right);
//     }
// public:
//     bool isValidBST(TreeNode* root) {
//         vec.clear(); // 不加这句在leetcode上也可以过，但最好加上
//         traversal(root);
//         for (int i = 1; i < vec.size(); i++) {
//             // 注意要小于等于，搜索树里不能有相同元素
//             if (vec[i] <= vec[i - 1]) return false;
//         }
//         return true;
//     }
// };