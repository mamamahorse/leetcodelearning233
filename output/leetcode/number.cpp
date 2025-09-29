// #include <iostream>
// using namespace std;
// int main()
// {
//     string s;
//     while(cin>>s)
//     {
//         int fast=s.size()-1;
//         int count =0;
//         for(int i=0;i<s.size();i++)
//         {
//             if(s[i]>='0'&&s[i]<='9')
//             count++;
//         }
//         s.resize(s.size()+count*5);
//         int slow= s.size()-1;
//         while(fast>=0)
//         {
//             if(s[fast]>='0'&&s[fast]<='9')
//             {
//                 s[slow--]='r';
//                 s[slow--]='e';
//                 s[slow--]='b';
//                 s[slow--]='m';
//                 s[slow--]='u';
//                 s[slow--]='n';
//             }
//             else
//             {
//                 s[slow--]=s[fast];
//             }
//             fast--;
//         }
//         cout<<s<<endl;;
//     }
// }

