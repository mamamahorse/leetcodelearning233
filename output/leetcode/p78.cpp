class Solution 
{
private:
vector<vector<int>> result;
vector<int> path;
void backtracking (vector<int>& nums, int startindex)
{   result.push_back(path);
    if(startindex>=nums.size())
    return;
    for(int i=startindex;i<nums.size();i++)
    {   if(i>startindex && nums[i]==nums[i-1])
        continue;
        path.push_back(nums[i]);
        backtracking(nums,i+1);
        path.pop_back();
    }   

}

public:
vector<vector<int>> subsetsWithDup(vector<int>& nums) 
{
    result.clear();
    path.clear();
    sort(nums.begin(),nums.end());
    backtracking(nums,0);
    return result;
}
};