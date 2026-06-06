#include <iostream>
#include <vector>

using namespace std;

long long total_ans = 0;

void merge (vector<int>& a, int left, int mid, int right)
{
    vector<int> temp(right-left + 1);
    int i=left;
    int j=mid + 1;
    int k =0;
    long long left_sum =0;
    for(int p = left; p<=mid; p++)
    left_sum += a[p];

    while(i<=mid && j <= right)
    {
        if(a[i]>a[j])
        {
            total_ans += left_sum - (long long)(mid - i + 1)*a[j];
            temp[k++] = a[j++];
        }
        else{
            left_sum -= a[i];
            temp[k++] = a[i++];
        }
    }

    while (i<=mid)
    temp[k++] = a[i++];
    while (j<= right)
    temp[k++]=a[j++];
    for (int p = 0; p < k; ++p) a[left + p] = temp[p];
}
void merge_sort(vector<int>& a, int left, int right) 
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort(a, left, mid);
    merge_sort(a, mid + 1, right);
    merge(a, left, mid, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    merge_sort(a, 0, n - 1);

    cout << total_ans << endl;

    return 0;
}