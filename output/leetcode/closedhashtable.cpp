#include <iostream>
#include <vector>
using namespace std;
//x%M   输入 N M K
int main() 
{ int n,N,M,K;
    while(cin>>n)
    { while(n--)
        {
        cin>>N>>M>>K;
        vector<int> hashtable(M,0);

        for(int i=0;i<N;i++)
        { int key;
            cin>>key;
            int index=key%M;
            hashtable[index]++;
        }
        cout<<hashtable[K]<<endl;
    }
    }

}
