#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canMake(const vector<int>& bloomDay, int m, int k, int days) 
{
    int bouquet = 0; // 已制作的花束数量
    int flower = 0;  // 当前连续盛开的花的数量
    for (int d : bloomDay) 
    {
        if (d <= days) 
        {
            flower++;
            if (flower == k) 
            {
                bouquet++;
                flower = 0; // 凑够一束，重新计数
            }
        }
         else 
        {
            flower = 0; // 遇到未开放的花，连续中断
        }
        if (bouquet >= m) return true;
    }
    return bouquet >= m;
}

int main() 
{
    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<int> bloomDay(n);
    int max_d = 0;
    for (int i = 0; i < n; ++i) 
    {
        cin >> bloomDay[i];
        if (bloomDay[i] > max_d) max_d = bloomDay[i];
    }
    
    if (1LL * m * k > n) 
    {
        cout << -1 << endl;
        return 0;
    }
    
    int low = 1, high = max_d;
    int ans = max_d;
    
    while (low <= high) 
    {
        int mid = low + (high - low) / 2;
        if (canMake(bloomDay, m, k, mid)) 
        {
            ans = mid;      
            high = mid - 1; 
        } else {
            low = mid + 1;  
        }
    }
    
    cout << ans << endl;
    
    return 0;
}