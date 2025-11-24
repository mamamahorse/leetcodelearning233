#include <iostream>
#include <vector>
#include <list>
using namespace std;
void dfs(const vector<list<int>>&graph,int key,vector<bool>& visited)
{
    if(visited[key])
    return;
    visited[key]=true;
    list<int> keys=graph[key];
    for(int key:keys)
    {
        dfs(graph,key,visited);
    }
}
int main()
{
    int n,m,s,t;
    cin>>n>>m;
    vector<list<int>> graph(n+1);
    while(m--)
    {
        cin>>s>>t;
        graph[s].push_back(t);
    }
    vector <bool> visited(n+1,false);
    dfs(graph,1,visited);
    for (int i = 1; i <= n; i++) 
    {
        if (visited[i] == false) 
        {
            cout << -1 << endl;
            return 0;
        }
    }
    cout << 1 << endl;

}