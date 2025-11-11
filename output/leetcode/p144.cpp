// class Solution {
// public:
//     void traversal(TreeNode*cur,vector<int>& r)
//         {  if(cur==NULL)
//             return;
//             r.push_back(cur->val);
//             traversal(cur->left,r);
//              traversal(cur->right,r);

//         }
        
//     vector<int> preorderTraversal(TreeNode* root) 
//     {  vector <int> result;
//         traversal(root,result);
//         return result;
//     }
// };    //前序 preorder
//  class Solution {
// public:
//     void traversal(TreeNode*cur,vector<int>& r)
//         {  if(cur==NULL)
//             return;
           
//             traversal(cur->left,r);
//              r.push_back(cur->val);
//              traversal(cur->right,r);

//         }
//     vector<int> inorderTraversal(TreeNode* root) 
//     {  vector <int> result;
//         traversal(root,result);
//         return result;
//     }
// }; //中序
// //后序同理
//  class Solution {
// public:
//     void traversal(TreeNode*cur,vector<int>& r)
//         {  if(cur==NULL)
//             return;
           
//             traversal(cur->left,r);
//               traversal(cur->right,r);
//              r.push_back(cur->val);
           

//         }
//     vector<int> postorderTraversal(TreeNode* root) 
//     {  vector <int> result;
//         traversal(root,result);
//         return result;
//     }
// }; 