#include <iostream>
#include <vector>
using namespace std;
int hashfunc(const string s)
{
    int h=0;
    for(int i=0;i<s.size();i++)
    {
        h=(h*12+(s[i]-'A'))%10007;
    }
    return h;
}
int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        int M,N;
        cin>>M>>N;
        vector<string> allstr(M);
        vector <pair<string,int>> table(10007,{"-",0});
        vector<string> check(N);
        for(int i=0;i<M;i++)
        {
            cin>>allstr[i];
        }
        for(int i=0;i<N;i++)
        {
            cin>>check[i];
        }
        for(int i=0;i<M;i++)
        {
            int h=hashfunc(allstr[i]);
                while (table[h].first != "-" && table[h].first != allstr[i])
            {
                h = (h + 1) % 10007;
            }
            table[h].first = allstr[i];
            table[h].second++;
        }
        for (int j = 0; j < N; j++)
        {
            int h = hashfunc(check[j]);
            int count = 0;
            int start = h;
            while (table[h].first != "-" && table[h].first != check[j])
            {
                h = (h + 1) % 10007;
                if (h == start) 
                break; 
            }
            if (table[h].first == check[j])
                count= table[h].second;

            cout << count;
            if (j != N - 1) 
            cout << " "; 
        }
        cout << endl;
    
    }
}