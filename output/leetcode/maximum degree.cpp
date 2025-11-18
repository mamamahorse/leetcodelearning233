#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int m;
    if (!(cin >> m))
     return 0;
    while (m--)
    {
        int N, C;
        cin >> N >> C;
        vector<int> indeg(N + 1, 0);
        for (int i = 0; i < C; ++i)
        {
            int u, v;
            cin >> u >> v;
            if (v >= 1 && v <= N) indeg[v]++;
        }
        int mx = 0;
        for (int i = 1; i <= N; ++i) 
        {
            if (indeg[i] > mx) mx = indeg[i];
        }
        cout << mx << endl;
    }
    return 0;
}