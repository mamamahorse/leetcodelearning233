// #include <iostream>
// #include <string>
// using namespace std;


// class Solution {
// public:
//     int strStr(string haystack, string needle) 
//     { 
//          for(int i=0;i<haystack.size();i++)
//         { if(needle[0]==haystack[i])
//             {   int count =0;
//                 for(int j=0;j<needle.size()&&j+i<haystack.size();j++)
//                 {  
                
//                     if(needle[j]==haystack[j+i])
//                     count++;
                
               
//             }

//                 if(count==needle.size())
//                 return i;
//             }

//         }
//         return -1;
//     }
// };