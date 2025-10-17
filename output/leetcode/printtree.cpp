// #include <iostream>
// #include <string>
// #include <queue>
// using namespace std;
// struct TreeNode
// {
//     char val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
// };


// //提供的是preorder，需要先构建树，叶子结点大写
// TreeNode* buildTree(const string &s,int &i) 
// {      if(i>=s.size()) 
//         return nullptr; // 边界保护
//     char c=s[i++];
//         if(c>='A'&&c<='Z')
//         return new TreeNode(c); //递归终止条件
//         TreeNode* root=new TreeNode(c);
//         root->left=buildTree(s,i);
//         root->right=buildTree(s,i);//i+2可不可以？
//         return root;
// }
// //不行。你不知道左右子树有多大。

// void printTree(TreeNode* root) 
// { 
//     queue<TreeNode*> q;
//     if(root==NULL)
//     return;
//     q.push(root);
//     while(!q.empty())
//     {
//         int size=q.size();
//         for(int i=0;i<size;i++)
//         {
//             TreeNode* node=q.front();
//             q.pop();
//             if(node)
//             {
//                 cout<<node->val;
//                 q.push(node->left);
//                 q.push(node->right);
//             }
//         }
//     }

// }

// int main()
// { int n=0;
//    while(cin>>n)
//    { while(n--)
//     {
//         string s;
//         cin>>s;
//         int i=0;
//         TreeNode* root=buildTree(s,i);
//         printTree(root);
//         cout<<endl;
//     }

//    }
// }