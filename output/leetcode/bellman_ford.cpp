#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int main()
{
    int n,m,p1,p2,val;
    cin>>n>>m;
    vector<vector<int>> adj;
    for(int i=0;i<m;i++)
    {
        cin>>p1>>p2>>val;
        adj.push_back({p1,p2,val});
    }
    int start=1;
    int end=n;
    vector<int> minDist(n+1,INT_MAX);
    minDist[start]=0;
    for(int i=0;i<n;i++)
    {
        for(vector<int> &side :adj)
        {
            int from=side[0];
            int to=side[1];
            int price=side[2];
            if(minDist[from]!=INT_MAX&& minDist[from]+price<minDist[to])
            {
                minDist[to]=minDist[from]+price;
            }
        }
    }
    
    if(minDist[end]==INT_MAX)
    cout<<"unconnected"<<endl;
    else
    cout<<minDist[end]<<endl;
}