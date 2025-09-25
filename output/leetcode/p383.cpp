// #include <string>
// using namespace std;
// class Solution
// {public:
//     bool canConstruct(string ransomNote, string magazine)
//     {
//         for(int i=0;i<magazine.length();i++)
//         {
//             for(int j=0;j<ransomNote.length();j++)
//             {
//                 if(magazine[i]==ransomNote[j])
//                 {
//                 ransomNote.erase(ransomNote.begin()+j);
//                 break;    
//                 }

//             }
//         }
//         if(ransomNote.empty())
//         return true;
//         return false;
//     }

// };