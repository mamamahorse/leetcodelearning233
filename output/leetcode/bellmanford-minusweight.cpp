#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;

int main() {
    int n, m, p1, p2, val;
    cin >> n >> m;

    vector<vector<int>> grid;

    for(int i = 0; i < m; i++)
    {
        cin >> p1 >> p2 >> val;
        // p1 指向 p2，权值为 val
        grid.push_back({p1, p2, val});

    }
    int start=1;
    int end=n;
    vector<int>minDist (n+1,INT_MAX);
    minDist[start]=0;
    bool flag=false;
    for(int i=0;i<n+1;i++)
    {
        for(vector<int>&side : grid)
        {
            int from=side[0];
            int to=side[1];
            int weight=side[2];
            if(i<n)//这次松弛n次，如果有可以继续松弛的，说明有负权回路。
            {
                if(minDist[from]!=INT_MAX&&minDist[to]>minDist[from]+weight)
                minDist[to]=minDist[from]+weight;
            }
            else
            {
                if (minDist[from] != INT_MAX && minDist[to] > minDist[from] + weight) 
                flag = true;
            }

        }
    }
    if(flag)
    cout<<"circle"<<endl;
    else if(minDist[end]==INT_MAX)
    {
        cout<<"unconnected"<<endl;
    }
    else
    cout<<minDist[end]<<endl;
}