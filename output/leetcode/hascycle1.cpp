#include <iostream>
#include <vector>
#include <queue>
using namespace std;
bool hascycle(int n,vector<vector<int>>& adj)
{
    vector<int> indeg(n+1,0);
    for(int i=1;i<n+1;i++)
    {
        for(int v: adj[i])
        {
            indeg[v]++;
        }
    }
    queue<int> q;
    for(int i=1;i<n+1;i++)
    {if(indeg[i]==0)
        q.push(i);
    }
    int count=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop(); 
        count++;
        for(int v: adj[u])
        {
            indeg[v]--;
            if(indeg[v]==0)
            {
                q.push(v);
            }
        }
    }
    return count != n;
}
int main()
{
    int m;
    cin>>m;
    while(m--)
    {
        int n,e;
        cin>>n>>e;
           vector<vector<int>> adj(n + 1);

        for (int i = 0; i < e; i++) 
        {
            int u, v;
            cin >> u >> v; // 有向边 u -> v
            adj[u].push_back(v);
        }

        cout << (hascycle(n, adj) ? "YES" : "NO") << endl;
    }
}