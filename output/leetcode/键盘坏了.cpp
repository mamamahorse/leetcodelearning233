#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<bool> can_use(26, false);
    for (int i = 0; i < k; i++) {

        char c;
        cin >> c;
        can_use[c - 'a'] = true;
    }

    long long ans = 0;      // 存储最终结果，用 long long 防止溢出
    long long cnt = 0;      // 记录当前连续可用段的长度

    for (int i = 0; i < n; i++) 
    {
        if (can_use[s[i] - 'a']) {
            // 如果当前字符可用，长度加 1
            cnt++;
        } else {
            // 如果遇到不可用字符，结算当前连续段
            ans += (cnt * (cnt + 1)) / 2;
            cnt = 0; // 重置计数器
        }
    }

    // 最后一段如果以可用字符结尾，也需要结算
    ans += (cnt * (cnt + 1)) / 2;

    cout << ans << endl;

    return 0;
}