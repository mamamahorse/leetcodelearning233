#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int N, M;
    if (cin >> N >> M) {
        vector<int> indegree(N, 0);
        vector<vector<int>> adj(N); // 邻接表，节省空间
        
        // 读取边
        for(int i = 0; i < M; i++) 
        {
            int x, y;
            cin >> x >> y;
            // 假设输入节点为 0 ~ N-1
            adj[x].push_back(y);
            indegree[y]++;
        }

        queue<int> q;
        for(int i = 0; i < N; i++) 
        {
            if(indegree[i] == 0) q.push(i);
        }

        vector<int> result;
        while(!q.empty()) 
        {
            int u = q.front(); 
            q.pop();
            result.push_back(u);

            // 遍历邻居 (效率比矩阵高，不需要扫描无关节点)
            for(int v : adj[u]) 
            {
                indegree[v]--;
                if(indegree[v] == 0) 
                {
                    q.push(v);
                }
            }
        }

        // 输出
        if(result.size() == N) 
        {
            for(int i=0;i<result.size()-1;i++)
             cout << result[i] << " ";
             cout<<result[result.size()-1]<<endl;
        }
         else
          {
            cout <<-1<<endl;
        }
    }
    return 0;
}