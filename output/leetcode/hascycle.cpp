#include <iostream>
#include <vector>
using namespace std;

bool hasCycle(int node, vector<vector<int>>& adj, vector<int>& state) {
    state[node] = 1; // visiting
    for (int n : adj[node]) {
        if (state[n] == 0) {
            if (hasCycle(n, adj, state)) return true;
        } else if (state[n] == 1) return true;
    }
    state[node] = 2; // visited
    return false;
}

int main() {
    int m;
    cin >> m;
    for (int test = 0; test < m; test++) {
        int n, e;
        cin >> n >> e;
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < e; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }
        vector<int> state(n + 1, 0);
        bool cycle = false;
        for (int i = 1; i <= n; i++) {
            if (state[i] == 0) {                        
                if (hasCycle(i, adj, state)) {
                    cycle = true;
                    break;
                }
            }
        }
        cout << (cycle ? "YES" : "NO") << endl;
    }
    return 0;
}