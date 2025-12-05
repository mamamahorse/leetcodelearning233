#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> adj;
vector<bool> visited;
void dfs(int u)
{
    visited[u]=true;
    for(int v=0;v<n;v++)
    {
        if(adj[u][v]==1&&!visited[v])
        {
            dfs(v);
        }
    }
}
int main() 
{
    cin >> n;
    adj.resize(n, vector<int>(n));
    visited.resize(n, false);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> adj[i][j];
        }
    }

    int componentCount = 0;
    for (int i = 0; i < n; i++) 
    {
        if (!visited[i]) 
        {
            componentCount++; 
            dfs(i);        
        }
    }
    cout << componentCount << endl;
    return 0;
}