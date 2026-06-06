#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    string s;
    if(!(cin>>n>>s))
    return 0;

    stack<int> sj;
    sj.push(-1);

    int maxlen = 0;

    for (int i=0; i<n; i++)
    {
        if(s[i] == '(')
        {
            sj.push(i);
        }
        else
        {
            sj.pop();
            if(sj.empty())
            {
                sj.push(i);
            }
            else
            {
                maxlen = max(maxlen, i- sj.top());
            }
        }
    }
    cout << maxlen << endl;
}
