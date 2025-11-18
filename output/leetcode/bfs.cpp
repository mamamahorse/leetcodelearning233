#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    int m;
    cin >> m;
    for (int test = 0; test < m; test++) {
        int n, e, s;
        cin >> n >> e >> s;
        vector<vector<int>> adj(n);
        for (int i = 0; i < e; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            sort(adj[i].begin(), adj[i].end());
        }
        vector<bool> visited(n, false);
        vector<int> order;
        queue<int> q;
        q.push(s);
        visited[s] = true;
        order.push_back(s);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int n : adj[node]) {
                if (!visited[n]) {
                    visited[n] = true;
                    order.push_back(n);
                    q.push(n);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            cout << order[i];
        }
        cout << endl;
    }
    return 0;
}