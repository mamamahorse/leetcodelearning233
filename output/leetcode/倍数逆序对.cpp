#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

// 临时数组，用于归并排序
ll temp[100005];

ll mergeSort(vector<ll>& a, int l, int r) {
    if (l >= r) return 0;

    int mid = l + (r - l) / 2;
    ll count = mergeSort(a, l, mid) + mergeSort(a, mid + 1, r);

    // 2. 核心统计步骤：统计跨越左右两个区间的数对
    // 此时 a[l...mid] 和 a[mid+1...r] 已经在递归中排好序了
    int j = mid + 1;
    for (int i = l; i <= mid; i++) 
    {
        // 使用双指针寻找满足 a[i] > 2 * a[j] 的最大范围
        // 注意：2 * a[j] 可能会溢出 int，因此 a[i] 需用 long long 且逻辑判断要小心
        while (j <= r && a[i] > 2 * a[j]) 
        {
            j++;
        }
        // 对于当前的 a[i]，右边有 (j - (mid + 1)) 个数满足条件
        count += (j - (mid + 1));
    }

    // 3. 经典的归并排序合并过程（从小到大排序）
    int p1 = l, p2 = mid + 1, p = l;
    while (p1 <= mid && p2 <= r) {
        if (a[p1] <= a[p2]) temp[p++] = a[p1++];
        else temp[p++] = a[p2++];
    }
    while (p1 <= mid) temp[p++] = a[p1++];
    while (p2 <= r) temp[p++] = a[p2++];

    for (int i = l; i <= r; i++) a[i] = temp[i];

    return count;
}

int main() {

    int n;
    if (!(cin >> n)) return 0;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << mergeSort(a, 0, n - 1) << endl;

    return 0;
}