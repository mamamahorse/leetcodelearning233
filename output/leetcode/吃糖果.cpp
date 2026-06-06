#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canFinish(const vector<int>& candies, int h, int k) 
{
    long long hours = 0; 
    for (int c : candies) 
    {
        // 计算当前这堆需要的小时数：c/k 向上取整
        hours += (c + k - 1) / k;
    }
    return hours <= h;
}

int main() 
{
    int n;
    long long h;
    if (!(cin >> n >> h)) return 0;

    vector<int> candies(n);
    int max_val = 0;
    for (int i = 0; i < n; ++i) 
    {
        cin >> candies[i];
        if (candies[i] > max_val) max_val = candies[i];
    }
    // 二分查找最小速度 k
    int left = 1, right = max_val;
    int ans = max_val;
    while (left <= right) 
    {
        int mid = left + (right - left) / 2;
        if (mid == 0) {
            left = 1;
            continue;
        }
        if (canFinish(candies, h, mid)) {
            ans = mid;       // 当前速度行得通，尝试更小的速度
            right = mid - 1;
        } else {
            left = mid + 1;  // 速度太慢了，需要加点速
        }
    }

    cout << ans << endl;

    return 0;
}