// class Solution {
// public:
//     int maxDepth = INT_MIN;
//     int result;
//     void traversal(TreeNode* root, int depth) 
//     {
//         if (root->left == NULL && root->right == NULL) 
//         {
//             if (depth > maxDepth) 
//             {
//                 maxDepth = depth;
//                 result = root->val;
//             }
//             return;
//         }
//         if (root->left) 
//         {
//         }// 保证先左再右
//         if (root->right) 
//         {
//             traversal(root->right, depth + 1); 
//         return;
//     }
//     int findBottomLeftValue(TreeNode* root) 
//     {
//         traversal(root, 0);
//         return result;
//     }
// };

// class Solution 
// {
// public:
//     int findBottomLeftValue(TreeNode* root) 
//     { queue<TreeNode*> que;
//      if(root!=NULL)
//      que.push(root);
//      int result=0;
//      while(!que.empty())
//      {
//         int size=que.size();
//         for(int i=0;i<size;i++)
//         {
//             TreeNode* node=que.front();
//             que.pop();
//             if(i==0)
//             result=node->val;
//             if(node->left)
//             que.push(node->left);
//             if(node->right)
//             que.push(node->right);
//         }
//      } 
//      return result; 
//     }  
// };//层序遍历