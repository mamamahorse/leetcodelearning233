// class Solution {
// public:
     
//     vector<vector<int>> result;
//         vector<int> path;
//         void traversal(TreeNode* cur, int count) 
//         { if(!cur->left&&!cur->right&&count==0)
//             {
//                 result.push_back(path);
//                 return;
//             }
//             if(!cur->left&&!cur->right)
//             return;
//             if(cur->left)
//             {
//                 count-=cur->left->val;
//                 path.push_back(cur->left->val);
//                 traversal(cur->left,count);
//                 count+=cur->left->val;
//                 path.pop_back();
//             }
//               if (cur->right) 
//               { 
//             path.push_back(cur->right->val);
//             count -= cur->right->val;
//             traversal(cur->right, count);  
//             count += cur->right->val;       
//             path.pop_back();               
//             }
//             return ;
//         }
//             vector<vector<int>> pathSum(TreeNode* root, int targetSum)
//             {
//                 result.clear();
//                 path.clear();
//                 if(root==NULL)
//                 return result;
//                 path.push_back(root->val);
//                 traversal(root,targetSum-root->val);
//                 return result;
//             }   
//         };