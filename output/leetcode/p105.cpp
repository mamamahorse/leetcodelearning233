// class Solution {
// private:
//         TreeNode* traversal (vector<int>& inorder, int inorderBegin, int inorderEnd, vector<int>& preorder, int preorderBegin, int preorderEnd) 
//         {
//         if (preorderBegin == preorderEnd) 
//         return NULL;

//         int rootValue = preorder[preorderBegin]; 
//         TreeNode* root = new TreeNode(rootValue);

//         if(preorderEnd - preorderBegin == 1)
//         return root;
//         int Index=0;
//         for(Index = inorderBegin; Index < inorderEnd; Index++) 
//         {
//             if (inorder[Index] == rootValue) break;
//         }  // 找到中序遍历的切割点
//         int leftbegin=inorderBegin;
//         int leftend=Index;
//         int rightbegin=leftend+1;
//         int rightend=inorderEnd;

//         int leftpreorderbegin=preorderBegin+1;
//         int leftpreorderend=preorderBegin+1+(leftend-leftbegin);
//         int rightpreorderbegin=preorderBegin+1+(leftend-leftbegin);
//         int rightpreorderend=preorderEnd;

//         root->left = traversal(inorder, leftbegin, leftend, preorder, leftpreorderbegin,leftpreorderend);
//         root->right = traversal(inorder, rightbegin, rightend, preorder, rightpreorderbegin,rightpreorderend);

        
//         return root;
//     }

// public:
//     TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//         if (inorder.size() == 0 || preorder.size() == 0) return NULL;

//         // 参数坚持左闭右开的原则
//         return traversal(inorder, 0, inorder.size(), preorder, 0, preorder.size());
//     }
// };