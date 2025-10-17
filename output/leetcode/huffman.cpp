#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct Node 
{
    int val;
    char ch;
    Node *left;
    Node *right;
    Node(int f, char c = '\0', Node* l = nullptr, Node* r = nullptr)
        : val(f), ch(c), left(l), right(r) {}
};
struct Compare 
{
    bool operator()(Node* a, Node* b) 
    {
        return a->val > b->val;
    }
};//priorityqueue默认是大顶堆,a＞b则是小顶堆逻辑。

void getCodeLen(Node* root, unordered_map<char, int>& codeLen, int depth) 
{
    if (!root) 
    return;
    if (!root->left && !root->right) 
    {
        codeLen[root->ch] = depth;
        return;
    }
    getCodeLen(root->left, codeLen, depth + 1);
    getCodeLen(root->right, codeLen, depth + 1);
}

int main() {
    int N;
    cin >> N;
    while (N--) 
    {
        int T;
        cin >> T;
        unordered_map<char, int> freq;
        for (int i = 0; i < T; i++) 
        {
            char c;
            int f;
            cin >> c >> f;
            freq[c] = f;
        }
        string s;
        cin >> s;

        priority_queue<Node*, vector<Node*>, Compare> huffman;
        for (auto& [c, f] : freq)
         huffman.push(new Node(f, c));

        // 只有一个字符时特判
        if (huffman.size() == 1) 
        {
            cout << freq[s[0]] * s.size() << endl;
            continue;
        }

        while (huffman.size() > 1) 
        {
            Node* a = huffman.top(); huffman.pop();
            Node* b = huffman.top(); huffman.pop();
            huffman.push(new Node(a->val + b->val, '\0', a, b));
        } //合并,最关键一步
        Node* root = huffman.top();

        // 获取编码长度
        unordered_map<char, int> codeLen;
        getCodeLen(root, codeLen, 0);

        // 计算总长度
        int totalLen = 0;
        for (char c : s)
            totalLen += codeLen[c];

        cout << totalLen << endl;
    }
    return 0;
}
