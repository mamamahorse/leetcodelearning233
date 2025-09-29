// #include <iostream>
// #include <stack>
// #include <algorithm>
// using namespace std;
// class Solution {
// public:
//     string removeDuplicates(string s) 
//     { stack<char> st;
//         for(int i=0;i<s.size();i++)
//         {if(st.empty()||st.top()!=s[i])
//          st.push(s[i]);
//          else if(i>0&&st.top()==s[i])
//          st.pop();
//         }
//        string result;
//        while(!st.empty())
//        {
//         result+=st.top();
//         st.pop();
//        }g
//            reverse(result.begin(),result.end());
//     return result;
//     }

// };