

// class Solution {
// public:
//     vector<int> preorderTraversal(TreeNode* root) 
//     {
//         stack<TreeNode*> st;
//         vector<int> result;
//         if (root == NULL) return result;
//         st.push(root);
//         while (!st.empty()) {
//             TreeNode* node = st.top();                       
//             st.pop();
//             result.push_back(node->val);
//             if (node->right) st.push(node->right);          
//             if (node->left) st.push(node->left);             
//         }
//         return result;
//     }
// };   //preorder
// class Solution {
// public:
//     vector<int> inorderTraversal(TreeNode* root) 
//     {
//         vector<int> result;
//         stack<TreeNode*> st;
//         TreeNode* cur = root;
//         while (cur != NULL || !st.empty()) 
//         {
//             if (cur != NULL) 
//             { 
//                 st.push(cur); 
//                 cur = cur->left;             // 找到最左边最底层的结点
//                                             //那是一切的开端
//             } 
//             else 
//             {
//                 cur = st.top();         //回溯到中，右
//                 st.pop();
//                 result.push_back(cur->val);     // 中
//                 cur = cur->right;               // 右
//             }
//         }
//         return result;
//     }
// };
// //后序是左右中，前序是中左右，只需要把前序的代码左右互换再reverse就可以了
//以下是统一风格的迭代遍历法
// class Solution {
// public:
//     vector<int> inorderTraversal(TreeNode* root) {
//         vector<int> result;
//         stack<TreeNode*> st;
//         if (root != NULL) 
//         st.push(root);
//         while (!st.empty()) 
//         {  TreeNode* node =st.top();
//             if(node!=NULL)
//             { st.pop();
//                 if(node->right)
//                 st.push(node->right);
//                 st.push(node);
//                 st.push(NULL);       //只有碰到NULL的时候才往result里面加
//                 if(node->left)   // 
//                 st.push(node->left);
//             }
//             else
//             {st.pop();
//              node = st.top();
//              st.pop();
//              result.push_back(node->val);
//             }
            
//         }
//         return result;
//     }
// };