#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

TreeNode* insertBST(TreeNode* root, int val) 
{
    if (!root) 
    return new TreeNode(val);
    if (val < root->val)
     root->left = insertBST(root->left, val);
    else 
    root->right = insertBST(root->right, val);
    return root;
}

void postorder(TreeNode* root, vector<int>& res) 
{
    if (!root) 
    return;
    postorder(root->left, res);
    postorder(root->right, res);
    res.push_back(root->val);
}

void inorder(TreeNode* root, vector<int>& res) 
{
    if (!root) return;
    inorder(root->left, res);
    res.push_back(root->val);
    inorder(root->right, res);
}

int main() {
    int T;
    cin >> T;
    cin.ignore(); // 忽略换行

    while (T--) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string val;
        TreeNode* root = nullptr;

        // 构建BST
        while (ss >> val) 
        {
            if (val == "n") continue;
            root = insertBST(root, stoi(val));
        }

        int k;
        cin >> k;
        cin.ignore();

        // 后序遍历
        vector<int> post;
        postorder(root, post);
        for (int i = 0; i < post.size(); ++i) 
        {
            if (i) cout << " ";
            cout << post[i];
        }
        cout << endl;

        // 第 k 小
        vector<int> in;
        inorder(root, in);
        cout << in[k - 1] << endl;
        //中序遍历就是有序数列，存进数组里就可以通过索引找到。
    }
    return 0;
}
