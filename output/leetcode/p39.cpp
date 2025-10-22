// class Solution 
// {
// private:
//     vector<vector<int>> result;
//     vector<int> path;
//     void backtracking(vector<int>& candidates, int target, int sum, int startIndex) 
//     {
//         if (sum == target) 
//         {
//             result.push_back(path);
//             return;
//         }

       
//         for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) 
//         {//注意循环终止条件的剪枝,比在if里判断少了一层递归,提高效率
//             sum += candidates[i];
//             path.push_back(candidates[i]);
//             backtracking(candidates, target, sum, i); 注意这里是i不是i+1,因为可以重复选取自己
//             sum -= candidates[i];
//             path.pop_back();

//         }
//     }
// public:
//     vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
// {
//         result.clear();
//         path.clear();
//         sort(candidates.begin(), candidates.end()); // 剪枝需要排序!
//         backtracking(candidates, target, 0, 0);
//         return result;
//     }
// };