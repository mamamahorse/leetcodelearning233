// #include <iostream>
// using namespace std;
// struct TreeNode
// {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
// };

// int maxdepth(TreeNode*root)
// {
//     if(root==NULL)
//     return 0;
//     int leftdepth=maxdepth(root->left);
//     int rightdepth=maxdepth(root->right);
//     return 1+max(leftdepth,rightdepth);
// }
// int main() 
// {
//     TreeNode* root = new TreeNode(1);
//     root->left = new TreeNode(2);
//     root->right = new TreeNode(3);
//     root->left->left = new TreeNode(4);
//     root->left->right = new TreeNode(5);

//     cout << "最大深度为: " << maxdepth(root) << endl;
// }