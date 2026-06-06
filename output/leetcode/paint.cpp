#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
long long solve(const vector<int>& a, int l, int r, int h) 
{
    if (l > r) return 0;
    
    int min_h = a[l];
    for (int i = l + 1; i <= r; i++) 
    {
        if (a[i] < min_h) 
        {
            min_h = a[i];
        }
    }
    
    long long vertical_strokes = r - l + 1;
    
    long long horizontal_strokes = min_h - h;
    
    // 被最低点切分出的子区间需要递归处理
    int last = l;
    for (int i = l; i <= r; i++) 
    {
        if (a[i] == min_h) 
        {
            horizontal_strokes += solve(a, last, i - 1, min_h);
            last = i + 1;
        }
    }
    // 处理最后一个可能的子区间
    horizontal_strokes += solve(a, last, r, min_h);
    return min(vertical_strokes, horizontal_strokes);
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) 
    {
        cin >> a[i];
    }

    // 初始调用：处理 0 到 n-1 范围，初始已涂高度为 0
    cout << solve(a, 0, n - 1, 0) << endl;

    return 0;
}