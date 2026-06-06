#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

// 检查区间 [l, r] 是否为活性段
bool isActive(const vector<ll>& a, int l, int r) {
    int len = r - l + 1;
    if (len < 3) return true;
    if (len > 48) return false; // 斐波那契性质：长度过大必有三角形

    vector<ll> b;
    for (int i = l; i <= r; ++i) b.push_back(a[i]);
    sort(b.begin(), b.end());

    for (int i = 0; i < len - 2; ++i) {
        if (b[i] + b[i+1] > b[i+2]) return false; // 找到三角形，非活性
    }
    return true;
}

int main() 
{
    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];

    // dp[i] 存储最大研究价值，初始化为 -1 表示无法切分
    vector<ll> dp(n + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        // 只需要枚举到 48 即可，因为更长的段不可能是活性的
        for (int len = 1; len <= min(i, 48); len++) 
        {
            int prev = i - len;
            if (dp[prev] != -1 && isActive(a, prev + 1, i)) {
                dp[i] = max(dp[i], dp[prev] + v[len]);
            }
        }
    }

    cout << dp[n] << endl;

    return 0;
}