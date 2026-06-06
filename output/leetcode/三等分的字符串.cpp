#include <iostream>
#include <string>
#include <algorithm>
#include <string>

using namespace std;

// 核心函数：求字符串的“最小表示法/标准型”
string get_standard(string s) {
    // 递归终止条件：如果长度不能被 3 整除，无法继续分裂，直接返回原串
    if (s.length() % 3 != 0) {
        return string(s);
    }
    
    // 如果能被 3 整除，均分为 3 份
    size_t len = s.length() / 3;
    
    // 递归求出 3 个子串的标准型
    string s1 = get_standard(s.substr(0, len));
    string s2 = get_standard(s.substr(len, len));
    string s3 = get_standard(s.substr(2 * len, len));
    
    // 把这 3 个子串按字典序排序
    // 这样就可以消除由于位置不同带来的差异
    string parts[3] = {s1, s2, s3};
    sort(parts, parts + 3);
    
    // 拼接后返回，作为当前这一层的标准型
    return parts[0] + parts[1] + parts[2];
}

int main() {
    // 优化输入输出流速度
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    
    string s, t;
    cin >> s >> t;
    
    // 分别求出 S 和 T 的标准型，比较是否相同即可
    if (get_standard(s) == get_standard(t)) {
        cout << "happy happy happy\n";
    } else {
        cout << "oh no\n";
    }
    
    return 0;
}