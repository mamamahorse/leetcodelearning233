#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    int n;
    cin>>n;
    vector<int> a(n);
    for (int i=0; i<n; i++)
    {
        cin>>a[i];
    }
    if (n ==1)
    {
        cout<< a[0] << endl;
        return 0;
    }
 
    vector <vector<long long>> dp (n, vector<long long>(2));
    dp[0][0] = a[0];
    dp[0][1] = -1e18; 
    long long max_sum = a[0];

    for (int i = 1; i < n; ++i) 
    {
        dp[i][0] = max((long long)a[i], dp[i-1][0] + a[i]);
        
        // 1. 删除当前 i：直接取 dp[i-1][0]
        // 2. 之前删过了：取 dp[i-1][1] + a[i]
        dp[i][1] = max(dp[i-1][0], dp[i-1][1] + a[i]);
        
        max_sum = max({max_sum, dp[i][0], dp[i][1]});
    }

    cout << max_sum << endl;

    return 0;
}