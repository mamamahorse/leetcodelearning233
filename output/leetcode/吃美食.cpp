#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = 1e18; 

int main() {
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<ll> a(n + 1);
    vector<ll> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) 
    {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    // dp[i] 表示前 i 道美食划分为若干轮的最大收益（包含轮内a_i之和）
    vector<ll> dp(n + 1, -INF);
    dp[0] = 0;

    for (int i = k; i <= n; i++) {
        ll cur_max = -1, cur_min = INF;
        for (int j = i - 1; j >= max(0, i - (2 * k - 1)); j--) 
        {
            cur_max = max(cur_max, a[j + 1]);
            cur_min = min(cur_min, a[j + 1]);
            
            int len = i - j;
            if (len >= k && dp[j] != -INF) {
                dp[i] = max(dp[i], dp[j] + cur_max + cur_min + (pre[i] - pre[j]));
            }
        }
    }

    // 最终答案需要减去总的美味度之和
    // 因为公式推导为：Sum(各轮得分+各轮a_i) - TotalSum
    ll total_sum = pre[n];
    ll ans = -total_sum; // 对应吃 0 道的情况
    
    for (int i = k; i <= n; i++) {
        if (dp[i] != -INF) {
            ans = max(ans, dp[i] - (total_sum - pre[i]) - pre[i]); 
            // 注意：上面的 dp[i] 里已经加过一次 pre[i] 了
            // 这里简化为：ans = max(ans, dp[i] - total_sum)
        }
    }
    
    // 直接使用推导出的简洁公式：ans = max(dp[i] - total_sum)
    ans = -total_sum; // 初始为全浪费
    for (int i = 0; i <= n; i++) {
        if (i == 0 || i >= k) { // 合法的停止点：不吃，或者吃掉的部分能分轮
            if (dp[i] != -INF) {
                ans = max(ans, dp[i] - total_sum);
            }
        }
    }

    cout << ans << endl;

    return 0;
}