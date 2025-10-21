class Solution {
private:
    vector<vector<int>> result;
    vector<int> path; 
    void backtracking(int n, int k, int startIndex) 
    {
      if(path.size()==k)
        {
            result.push_back(path);
            return;
        }
        for(int i=startIndex;i<=n;++i)
        {//此处循环结束条件可以剪枝，若剩余元素个数不足以填满path，则无需继续
            path.push_back(i);
            backtracking(n,k,i+1);
            path.pop_back();//回溯 
        }//i<=n-(k-path.size())+1
    }
public:
    vector<vector<int>> combine(int n, int k)
     {
        result.clear(); 
        path.clear();  
        backtracking(n, k, 1);
        return result;
    }
};