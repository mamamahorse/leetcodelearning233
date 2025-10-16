// class Solution {
// public:
//     TreeNode* constructMaximumBinaryTree(vector<int>& nums) 
// {   TreeNode* node= new TreeNode(0);
//     if(nums.size()==1)
//     {
//         node->val=nums[0];
//         return node;
//     }
//     int maxvalue=INT_MIN;
//     int maxindex=0;
//     for(int i=0;i<nums.size();i++)
//     {
//         if(nums[i]>maxvalue)
//         {
//             maxvalue=nums[i];
//             maxindex=i;
//         }
//     }
//     node->val=maxvalue;
//     if(maxindex>0)
//     {
//         vector<int> leftnums(nums.begin(),nums.begin()+maxindex);
//         node->left=constructMaximumBinaryTree(leftnums);
//     }
//     if(maxindex<nums.size()-1)
//     {
//         vector<int> rightnums(nums.begin()+maxindex+1,nums.end());
//         node->right=constructMaximumBinaryTree(rightnums);
//     }
//     return node;
// }

// };