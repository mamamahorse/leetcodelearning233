// class Solution {
// public:
//     vector<int> preorderTraversal(TreeNode* root) 
//     {
//         stack<TreeNode*> st;
//         vector<int> result;
//         if (root == NULL) return result;
//         st.push(root);
//         while (!st.empty()) 
//         {
//             TreeNode* node = st.top();                    
//             result.push_back(node->val);
//             if (node->right) st.push(node->right);          
//             if (node->left) st.push(node->left);          
//         }
//         return result;
//     }
// };
//前序排列时，取top的时候，和中左右的顺序是一样的
//但是中序排列时，因为要从顶部开始，所以取top就不是左中右了
//这个逻辑无法像递归一样直接调换三个语句的顺序。
//后序排列是左右中，只需要把中右左取逆序。
//中序是左中右，左要一路探到底，然后回弹到他的父亲，然后再到右。
//因此迭代的写法要一路向左，然后pop一个，再push，再看右。