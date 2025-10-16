// class Solution 
// {
// public: 
//     void preOrderMorris(TreeNode* root) 
//     {
//         if (root == NULL)
//             return;
//         TreeNode* curr = root;  // 当前的结点
//         TreeNode* currLeft = NULL;  // 当前结点的左子树
//         while (curr != NULL) 
//         {
//             currLeft = curr->left;
//             // 当前结点的左子树存在即可建立连接
//             if (currLeft != NULL) 
//             {
//                 // 找到当前左子树的最右侧节点，并且不能沿着连接返回上层
//                 while (currLeft->right != NULL && currLeft->right != curr)
//                     currLeft = currLeft->right;
//                 //最右侧节点的右指针没有指向根
//创建连接并往下一个左子树的根结点进行连接操作 以上都是为了找左子树最右
//                 if (currLeft->right == NULL) 
//                 {
//                     currLeft->right = curr;
//                     curr = curr.left;
//                     continue;  // 这个continue很关键
//                 } 
//                 else 
//                 //当左子树的最右侧节点有指向根结点，说明访问完左子树
//                 //此时断开链接,相当于出栈
//                     currLeft->right = NULL;
//             } 
//             // 返回上层的阶段不断向右走
//             curr = curr.right;
//         }
//     }
// }
//morris遍历的核心思想是利用树中空闲指针来存储遍历信息，从而避免使用栈或递归。
//通过在遍历过程中动态地修改树的结构，实现了O(1)的空间复杂度,时间复杂度为O(n)。
//当你要去访问左子树时，先找到左子树中最右边的节点
//适用于前,中序遍历.
//把它的右指针临时指向当前节点（root），这样遍历完左子树后能沿着线索回到root,无需栈