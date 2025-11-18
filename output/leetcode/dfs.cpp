#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& order) 
{
    visited[node] = true;
    order.push_back(node);
    for (int n : adj[node]) 
    {
        if (!visited[n]) {
            dfs(n, adj, visited, order);
        }
    }
}

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
        dfs(s, adj, visited, order);
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            cout << order[i];
        }
        cout << endl;
    }
    return 0;
}