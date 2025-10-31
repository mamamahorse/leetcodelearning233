#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

TreeNode* buildTree(istringstream &iss) 
{
    string token;
    if (!(iss >> token)) 
    return nullptr;
    if (token == "-") 
    return nullptr;

    TreeNode* node = new TreeNode(stoi(token));
    node->left = buildTree(iss);
    node->right = buildTree(iss);
    return node;
}

void inorder(TreeNode* root, TreeNode*& prev, TreeNode*& first, TreeNode*& second) 
{ //prev记录上一个节点，first和second记录异常节点.
    if (!root) 
    return;
    inorder(root->left, prev, first, second);

    if (prev && prev->val > root->val) 
    {
        if (!first) 
        first = prev;
        second = root;
    }
    prev = root;

    inorder(root->right, prev, first, second);
}

void preorder(TreeNode* root) 
{
    if (!root) 
    {
        cout << "- ";
        return;
    }
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() 
{
    string line;
    getline(cin, line);
    istringstream iss(line);

    TreeNode* root = buildTree(iss);

    TreeNode *first = nullptr, *second = nullptr, *prev = nullptr;
    inorder(root, prev, first, second);

    if (first && second)
        swap(first->val, second->val);

    preorder(root);
    return 0;
}
