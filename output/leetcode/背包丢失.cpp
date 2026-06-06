#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }

    // dp[j] 表示容量为 j 的背包方案数
    // 因为只求末位，所有运算都对 10 取模
    vector<int> dp(m + 1, 0);
    dp[0] = 1;

    // 1. 先进行一遍完整的背包 DP
    for (int i = 1; i <= n; ++i) 
    {
        for (int j = m; j >= w[i]; --j) 
        {
            dp[j] = (dp[j] + dp[j - w[i]]) % 10;
        }
    }

    // 2. 对于每个物品 i，尝试从总结果中“减去”它
    for (int i = 1; i <= n; ++i) 
    {
        // 创建一个临时数组或者直接在 dp 上还原
        // 注意：还原时的顺序要和添加时相反（从小到大）
        vector<int> res = dp;
        for (int j = w[i]; j <= m; ++j) 
        {
            res[j] = (res[j] - res[j - w[i]] + 10) % 10;
        }

        // 输出结果
        for (int j = 1; j <= m; ++j) {
            cout << res[j] << (j == m ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}