#include <iostream>
#include <string>
#include <vector>

using namespace std;
void solve ()
{
    string a;
    cin >> a;
    vector<char> evens, odds;
    for (char c : a)
    {
        int val = c - '0';
        if (val % 2 == 0)
        {
            evens.push_back(c);
            
        }
        else
        {
            odds.push_back(c);
        }
    }

    string result = "";

    int i = 0, j = 0;
    while (i < evens.size() && j < odds.size())
    {
        if(evens[i]< odds[j])
        result += evens[i++];
        else
        result += odds[j++];
    }

    while(i < evens.size())
        result += evens[i++];
    while (j < odds.size())
        result += odds[j++];
    cout << result << endl;
}

int main()
{
    int t;
    if(!(cin>>t))
    return 0;


    while (t--)
    {
        solve();
    }

    return 0;
}