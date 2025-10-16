// class Solution 
// {
// public:
//     // 返回以该节点为根节点的二叉树的高度，如果不是平衡二叉树则返回-1
//     int getHeight(TreeNode* node) 
//     {
//         if (node == NULL) 
//           return 0;
// //递止终止条件
//         //看左右子树的高度差
//         int leftHeight = getHeight(node->left);
//         if (leftHeight == -1) 
//         return -1;
//         int rightHeight = getHeight(node->right);
//         if (rightHeight == -1) 
//         return -1;
//         return abs(leftHeight - rightHeight) > 1 ? -1 : 1 + max(leftHeight, rightHeight);
//     }
//     bool isBalanced(TreeNode* root) 
//     {
//         return getHeight(root) == -1 ? false : true;
//     }
// };