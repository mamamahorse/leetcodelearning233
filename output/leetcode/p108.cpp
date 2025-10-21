// class Solution 
// {
// private:
//     TreeNode* traversal(vector<int>& nums, int left, int right) 
//     {//左闭右闭
//         if (left > right) 
//         return nullptr;
//         int mid = left + ((right - left) / 2);//防溢出
//         TreeNode* root = new TreeNode(nums[mid]);
//         root->left = traversal(nums, left, mid - 1);
//         root->right = traversal(nums, mid + 1, right);
//         return root;
//     }
// public:
//     TreeNode* sortedArrayToBST(vector<int>& nums) 
//     {
//         TreeNode* root = traversal(nums, 0, nums.size() - 1);
//         return root;
//     }
// };

// class Solution {
// public:
//     TreeNode* sortedArrayToBST(vector<int>& nums) 
//     {if(nums.size==0)
//         return nullptr;

//         TreeNode *root=new TreeNode(0);
//         queue<TreeNode*> nodeque;
//         queue<int> leftque;
//         queue<int> rightque;
//         nodeque.push(root);
//         leftque.push(0);
//         rightque.push(nums.size()-1);

//     }
// };
// //如果用队列实现的话，需要同时维护三个队列
// //分别存储节点，左边界，右边界。每次从队列中取出一个节点和对应的边界，然后计算中点，创建节点值，并将左右子节点和对应的边界入队。