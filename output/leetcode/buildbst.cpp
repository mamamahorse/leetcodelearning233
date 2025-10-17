#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};
TreeNode* buildBST(TreeNode* root, int val) 
{
    if (!root) 
    return new TreeNode(val);
    if (val < root->val) 
    root->left = buildBST(root->left, val);
    else 
    root->right = buildBST(root->right, val);
    return root;
}
int maxdepth(TreeNode*root)
{
    if(root==NULL)
    return 0;
    int leftdepth=maxdepth(root->left);
    int rightdepth=maxdepth(root->right);
    return 1+max(leftdepth,rightdepth);
}

int main()
{
     string line;
     int n=0;
while(cin>>n)
{  cin.ignore();
    while (n--)
    {getline(cin, line);
        stringstream ss(line);
    vector<int> nums;
    int x;
    while(ss>>x)
    nums.push_back(x);
    TreeNode* root = nullptr;
    for(int i=0;i<nums.size();i++)
    root = buildBST(root, nums[i]);
    cout<<maxdepth(root)<<endl;
    }
}
}