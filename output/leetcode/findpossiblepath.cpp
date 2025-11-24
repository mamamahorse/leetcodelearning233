#include <iostream>
#include <vector>
using namespace std;
int n;
vector<int> father=vector<int> (101,0);
void init()
{
    for(int i=1;i<=n;i++)
    {
        father[i]=i;
    }
}
int find(int u)
{
    if(u==father[u])
    return u;
    else return father[u]=find(father[u]);
}
void join(int u,int v)
{
    u=find(u);
    v=find(v);
    if(u==v)
    return;
    father[v]=u;
}
bool isSame(int u,int v)
{
    u=find(u);
    v=find(v);
    return(u==v);


}

int main()
{
    int m,s,t;
    cin>>n>>m;
    int source,destination;
    init();
    while(m--)
    {
        cin>>s>>t;
        join(s,t);
    }
    cin>>source>>destination;
    if(isSame(source,destination))
    cout<<1<<endl;
    else
    cout<<0<<endl;
}