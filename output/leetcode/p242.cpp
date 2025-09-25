// #include <string>
// using namespace std;
// class Solution {
// public:
//     bool isAnagram(string s, string b) 
//     {
//       int arr[26]={0};
//       for(int i=0;i<s.size();i++)
//       arr[s[i]-'a']++;
//          for(int i=0;i<b.size();i++)
//       arr[b[i]-'a']--;
//       for(int j=0;j<26;j++)
//       if(arr[j])
//       return false;
//       return true;
//     }
// };