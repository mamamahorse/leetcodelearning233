#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
int main()
{   int n;
    scanf("%d",&n);
    vector<int> re1(n,0); 
    vector<int> re2(n+1,0);
    for(int i=0;i<n;i++)
    scanf("%d",&re1[i]);
    for(int j=1;j<n+1;j++)
    re2[j]=re2[j-1]+re1[j-1];
    int s1,s2;
    while(~scanf("%d %d",&s1,&s2))
    {  
        printf("%d\n",re2[s2+1]-re2[s1]);
    }

}
