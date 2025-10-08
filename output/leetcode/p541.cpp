// #include <iostream>
// #include <string>
// #include <vector>
// using namespace std;

// class Solution {
// public:
//     string reverse(string s) 
//     { for(int i=0;i<s.size()/2;i++)
//         {
//             s[i]^=s[s.size()-i-1];
//             s[s.size()-i-1]^=s[i];
//              s[i]^=s[s.size()-i-1];
//         }
//         return s;
//     }
//     string reverseStr(string s, int k) 
//     { for(int i=0;i<s.size();i+=k*2)
//         {if(i+k<=s.size())
//             {
//             string sub=reverse(s.substr(i,k));
//             s.replace(i, k, sub); 
//             }
//             else
//             {
//              string sub=reverse(s.substr(i));
//               s.replace(i,sub.size(),sub); 
//             }



//         }
//         return s;
//     }
// };