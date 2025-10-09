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
// class Solution {
// public:
//     vector<int> inorderTraversal(TreeNode* root) {
//         vector<int> result;
//         stack<TreeNode*> st;
//         TreeNode* cur = root;
//         while (cur != NULL || !st.empty()) {
//             if (cur != NULL) { // 指针来访问节点，访问到最底层
//                 st.push(cur); // 将访问的节点放进栈
//                 cur = cur->left;                // 左
//             } else {
//                 cur = st.top(); // 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
//                 st.pop();
//                 result.push_back(cur->val);     // 中
//                 cur = cur->right;               // 右
//             }
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
//接下来是统一迭代法。
// class Solution {
// public:
//     vector<int> inorderTraversal(TreeNode* root)
//      {
//         vector<int> result;
//         stack<TreeNode*> st;
//         if (root != NULL) st.push(root);
//         while (!st.empty()) {
//             TreeNode* node = st.top();
//             if (node != NULL) 
//             {
//                 st.pop(); // 将该节点弹出，避免重复操作
//                 if (node->right) 
//                 st.push(node->right);  // 添加右节点（空节点不入栈）
//                 st.push(node);                         
//                 st.push(NULL); // 中节点访问过，但是还没有处理，加入空节点做为标记。
//                 if (node->left)
//                  st.push(node->left);    // 添加左节点（空节点不入栈）
//                  //只需要把上面代码调换，就可实现其他顺序，注意仍旧是在中结点后加入NULL
//             }
//              else 
//             { // 只有遇到空节点的时候，才将下一个节点放进结果集
//                 st.pop();           // 将空节点弹出
//                 node = st.top();    // 重新取出栈中元素
//                 st.pop();
//                 result.push_back(node->val); // 加入到结果集
//             }
//         }
//         return result;
//     }
// };
//以上代码对于中结点进行标记，遇到标记的时候才压入result
//如果一个结点没有标记，说明它的左子树还没有处理完，继续循环
//对比，好处是代码统一了，坏处是多了标记