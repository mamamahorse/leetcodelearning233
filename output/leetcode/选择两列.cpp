#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 优化输入输出
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> h1(n), h2(n);
    for (int i = 0; i < n; ++i) cin >> h1[i];
    for (int i = 0; i < n; ++i) cin >> h2[i];

    // dp[i][0]: 选第一排, dp[i][1]: 选第二排, dp[i][2]: 都不选
    // 为了节省空间，可以用三个变量滚动更新，或者直接开数组
    vector<vector<long long>> dp(n, vector<long long>(3, 0));

    // 初始化第一列
    dp[0][0] = h1[0];
    dp[0][1] = h2[0];
    dp[0][2] = 0;

    for (int i = 1; i < n; ++i) {
        // 当前选第一排，前一个必须是 选第二排 或 都不选
        dp[i][0] = max(dp[i-1][1], dp[i-1][2]) + h1[i];
        
        // 当前选第二排，前一个必须是 选第一排 或 都不选
        dp[i][1] = max(dp[i-1][0], dp[i-1][2]) + h2[i];
        
        // 当前都不选，取前一个选了某人的最大值
        dp[i][2] = max(dp[i-1][0], dp[i-1][1]);
    }

    // 最终答案是最后一列三个状态中的最大值
    long long ans = max({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
    cout << ans << endl;

    return 0;
}