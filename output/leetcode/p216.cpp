// class Solution {
// private:
//     vector<vector<int>> result;
//     vector<int> path; 
//     void backtracking(int targetSum, int k, int sum, int startIndex) 
//     {   if(sum>targetSum) return; //剪枝
//         if (path.size() == k) 
//         {
//             if (sum == targetSum) 
//             result.push_back(path);
//             return; //注意不能把第二个if合并，否则会漏掉return
//         }
//         for (int i = startIndex; i <= 9; i++) 
//         {
//             sum += i; // 处理
//             path.push_back(i); // 处理
//             backtracking(targetSum, k, sum, i + 1); 
//             sum -= i; // 回溯
//             path.pop_back(); // 回溯
//         }
//     }

// public:
//     vector<vector<int>> combinationSum3(int k, int n) 
//     {
//         result.clear(); // 可以不加
//         path.clear();   // 可以不加
//         backtracking(n, k, 0, 1);
//         return result;
//     }
// };
// //和p77高度相似