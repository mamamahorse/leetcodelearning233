// class Solution 
// {
// public:
//     TreeNode* trimBST(TreeNode* root, int low, int high) 
//     {
//         if (root == nullptr) return nullptr;
//         if (root->val < low) return trimBST(root->right, low, high);
//         if (root->val > high) return trimBST(root->left, low, high);
//         root->left = trimBST(root->left, low, high);
//         root->right = trimBST(root->right, low, high);
//         return root;
//     }
// };

// class Solution {
// public:
//     TreeNode* trimBST(TreeNode* root, int L, int R) 
//     {
//         if (!root) 
//         return nullptr;

//         while (root != nullptr && (root->val < L || root->val > R)) 
//         {
//             if (root->val < L) root = root->right; // 小于L往右走
//             else root = root->left; // 大于R往左走
//         } //处理root
//         TreeNode *cur = root;
//         // 此时root已经在[L, R] 范围内，处理左孩子
//         while (cur != nullptr) 
//         {
//             while (cur->left && cur->left->val < L) 
//             {
//                 cur->left = cur->left->right;
//             }//通过循环找到左子树中大于等于L的节点
//             cur = cur->left; //相当于一个pre和一个cur在移动。
//         }
//         cur = root;//重置

//         // 此时root已经在[L, R] 范围内，处理右孩子
//         while (cur != nullptr) 
//         {
//             while (cur->right && cur->right->val > R) 
//             {
//                 cur->right = cur->right->left;
//             }
//             cur = cur->right;
//         }
//         return root;
//     }
// };