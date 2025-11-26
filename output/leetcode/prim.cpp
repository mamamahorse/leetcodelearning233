#include<iostream>
#include<vector>
#include <climits>

using namespace std;
int main() {
    int v, e;
    int x, y, k;
    cin >> v >> e;
    // 填一个默认最大值，题目描述val最大为10000
    vector<vector<int>> grid(v + 1, vector<int>(v + 1, 10001));
    while (e--) {
        cin >> x >> y >> k;
        // 因为是双向图，所以两个方向都要填上
        grid[x][y] = k;
        grid[y][x] = k;

    }
    // 所有节点到最小生成树的最小距离
    vector<int> minDist(v + 1, 10001);

    // 这个节点是否在树里
    vector<bool> isInTree(v + 1, false);
   for(int i=1;i<v;i++) //prim第一步，选择距离生成树最近的节点
   {
    int cur=-1;
    int minval=INT_MAX;
    for(int j=1;j<=v;j++)
    {
        if(!isInTree[j]&& minDist[j]<minval)
        {
            minval=minDist[j];
            cur=j;
        }
    }
    isInTree[cur]=true;//第二步，找可连接的最短的边，标记，加入生成树   
    for(int j=1;j<=v;j++)//第三步，更新mindist数组，观察cur直接相连的点
    {
        if(!isInTree[j]&&grid[cur][j]<minDist[j])
        {
            minDist[j]=grid[cur][j];
        }
    }
   }
   int result=0;
   for(int i=2;i<=v;i++)//一定要记得，不计算第一个边的mindist，只有n-1条边，第一个点的距离是默认的，不算数
   {
    result+=minDist[i];
   }
   cout<<result<<endl;
   
}