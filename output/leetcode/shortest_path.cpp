#include <iostream>
#include <climits>
using namespace std;

const int MAXN = 2555;
const int INF = INT_MAX;

int g[MAXN][MAXN];
int dist[MAXN];
bool vis[MAXN];

int main() 
{
    int N, C, S, T;
    cin >> N >> C >> S >> T;

        for (int i = 1; i <= N; i++) 
        {
        for (int j = 1; j <= N; j++) 
        {
            if (i == j) g[i][j] = 0;
            else g[i][j] = INF;
        }
        }

    for (int i = 0; i < C; i++) 
    {
        int u, v, w;
        cin >> u >> v >> w;
        if (w < g[u][v]) 
        {  
            g[u][v] = w;
            g[v][u] = w;
        }
    }

    for (int i = 1; i <= N; i++) 
    dist[i] = INF;
    
    dist[S] = 0;

    for (int i = 1; i <= N; i++) 
    {
        int u = -1, mind = INF;
        for (int j = 1; j <= N; j++) 
        {
            if (!vis[j] && dist[j] < mind) 
            {
                mind = dist[j];
                u = j;
            }
        }

        if (u == -1) 
        break;
        vis[u] = true;
        for (int v = 1; v <= N; v++) 
        {
            if (!vis[v] && g[u][v] < INF) 
            {
                if (dist[v] > dist[u] + g[u][v]) 
                {
                    dist[v] = dist[u] + g[u][v];
                }
            }
        }
    }

    cout << dist[T] << endl;
    return 0;
}
