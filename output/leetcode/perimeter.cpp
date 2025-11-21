#include <iostream>
#include <vector>
using namespace std;
int count = 0; 
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; 
void dfs(vector<vector<int>>& grid, int x, int y) 
{
    // 标记为 2，代表“已访问的陆地”，这样它既不是 1（待访问），也不是 0（水）
    grid[x][y] = 2; 

    for (int i = 0; i < 4; i++) 
    { 
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];

// 越界
        if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) 
        {
            count++;
            continue;
        }

        // 情况2：邻居是水 -> 这一面是海岸线，贡献 1 周长
        if (grid[nextx][nexty] == 0) {
            count++;
            continue;
        }

        // 情况3：邻居是未访问的陆地 -> 递归进去
        if (grid[nextx][nexty] == 1) {
            dfs(grid, nextx, nexty);
        }
        
        // 情况4：邻居是 2 (已访问陆地) -> 内部边，不做任何操作，也不加分
    }
}
int dfs1(vector<vector<int>> grid,int x,int y)
{
    if(x<0||x>=grid.size()||y<0||y>=grid[0].size())
    {
        return 1;
    }
    if(grid[x][y]==0)
    {
        return 1;
    }
    if(grid[x][y]==2)
    {
        return 0;
    }
    grid[x][y]=2;
    return dfs1(grid,x+1,y) + dfs1(grid,x-1,y) + dfs1(grid,x,y+1) + dfs1(grid,x,y-1);
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> grid(n, vector<int>(m));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>grid[i][j];
        }
    }
     for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(grid[i][j]==1)
            {
                cout<<dfs1(grid,i,j)<<endl;
                break;
            }
        }
    }
}
