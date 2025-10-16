// class Solution {
// public:
//     TreeNode* cloneTree(TreeNode* root) 
//     {
//         if (!root) return nullptr;
//         TreeNode* newNode = new TreeNode(root->val);
//         newNode->left = cloneTree(root->left);
//         newNode->right = cloneTree(root->right);
//         return newNode;
//     }
//     TreeNode* invertTree(TreeNode* root) 
//     {
//         if (root == NULL) return root;
//         swap(root->left, root->right);
//         invertTree(root->left);
//         invertTree(root->right);
//         return root;
//     }
//     bool isSameTree(TreeNode* p, TreeNode* q) 
//     {
//         if (!p && !q) return true;
//         if (!p || !q) return false;
//         if (p->val != q->val) return false;
//         return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
//     }
//     bool isSymmetric(TreeNode* root) 
//     {
//         if (!root) return true;
//         TreeNode* copyRoot = cloneTree(root);  
//         invertTree(copyRoot);                  
//         return isSameTree(root, copyRoot);     
//     }
// };
// 判断对称，可以利用翻转树的代码，整个反转后若树不变，则对称。
// 复制树加入了额外的开销，可以避免。
// 以下在递归中比较，避免了复制。
// class Solution 
// {
// public:
//     bool isMirror(TreeNode* t1, TreeNode* t2) 
//     {
//         if (!t1 && !t2) return true;           
//         if (!t1 || !t2) return false;         
//         if (t1->val != t2->val) return false;  
//         return isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
//     }
//     bool isSymmetric(TreeNode* root) 
//     {
//         return isMirror(root->left, root->right);
//     }
//     };