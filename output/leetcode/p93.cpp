// class Solution 
// {
// private:
//     vector<string> result;
//     void backtracking(string& s, int startIndex, int pointNum) 
//     {
//         if (pointNum == 3) 
//         { // 逗点数量为3时，分隔结束
//             // 判断第四段子字符串是否合法，如果合法就放进result中
//             if (isValid(s, startIndex, s.size() - 1)) 
//             {
//                 result.push_back(s);
//             }
//             return;
//         }
//         for (int i = startIndex; i < s.size(); i++) 
//         {
//             if (isValid(s, startIndex, i)) 
//             { 
//                 s.insert(s.begin() + i + 1 , '.');  //insert是在迭代器之前插入，注意！
//                 pointNum++;
//                 backtracking(s, i + 2, pointNum); //+2是因为插入了点
//                 pointNum--;                         
//                 s.erase(s.begin() + i + 1);         // 回溯删掉逗点
//             }
//              else 
//              break; 
//         }
//     }
//     // 判断字符串s在左闭右闭区间[start, end]所组成的数字是否合法
//     bool isValid(const string& s, int start, int end) 
//     {
//         if (start > end) 
//         {
//             return false;
//         }
//         if (s[start] == '0' && start != end) 
//         {
//                 return false;
//         }
//         int num = 0;
//         for (int i = start; i <= end; i++) 
//         {
//             if (s[i] > '9' || s[i] < '0') 
//             { // 非数字字符
//                 return false;
//             }
//             num = num * 10 + (s[i] - '0');
//             if (num > 255) 
//             { // 如果大于255了不合法
//                 return false;
//             }
//         }
//         return true;
//     }
// public:
//     vector<string> restoreIpAddresses(string s) 
//     {
//         result.clear();
//         if (s.size() < 4 || s.size() > 12) return result; // 算是剪枝了
//         backtracking(s, 0, 0);
//         return result;
//     }
//     };