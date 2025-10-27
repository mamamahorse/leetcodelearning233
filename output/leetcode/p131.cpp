// class Solution 
// {
// private:
//     vector<vector<string>> result;
//     vector<string> path; 
//     void backtracking (const string& s, int startIndex) 
//     {
//         if (startIndex >= s.size()) //用==就可以
//         {
//             result.push_back(path);
//             return;
//         }
//         for (int i = startIndex; i < s.size(); i++) 
//         {
//             if (isPalindrome(s, startIndex, i)) 
//             {   
//                 string str = s.substr(startIndex, i - startIndex + 1);
//                 path.push_back(str);
//             } 
//             else 
//             {                               
//                 continue;
//             }
//             backtracking(s, i + 1); 
//             path.pop_back(); // 回溯
//         }
//     }
//     bool isPalindrome(const string& s, int start, int end) 
//     {
//         for (int i = start, j = end; i < j; i++, j--) 
//         {
//             if (s[i] != s[j]) 
//             {
//                 return false;
//             }
//         }
//         return true;
//     }
// public:
//     vector<vector<string>> partition(string s) 
//     {
//         result.clear();
//         path.clear();
//         backtracking(s, 0);
//         return result;
//     }
// };


// //判断回文串可以用动态规划的思想
//   void computePalindrome(const string& s) 
//   {
//         // isPalindrome[i][j] 代表 s[i:j](双边包括)是否是回文字串 
//         isPalindrome.resize(s.size(), vector<bool>(s.size(), false)); 
//         for (int i = s.size() - 1; i >= 0; i--) 
//         { 
//             // 需要倒序计算, 保证在i行时, i+1行已经计算好了
//             for (int j = i; j < s.size(); j++) 
//             {
//                 if (j == i) {isPalindrome[i][j] = true;}//单字符
//                 else if (j - i == 1) {isPalindrome[i][j] = (s[i] == s[j]);}
//                 else {isPalindrome[i][j] = (s[i] == s[j] && isPalindrome[i+1][j-1]);}
//             }//else利用了子问题的解，需要注意i+1要比i先算好，故逆序。
//         }
//     }