class Solution 
{
public:
    int wiggleMaxLength(vector<int>& nums) 
    {   if (nums.size()==1)
        return 1;
        if(nums.size()==2)
        {
            if(nums[0]==nums[1])
                return 1;
            else
                return 2;
        }
        vector<int> depth(nums.size(),0);
        for(int i=1;i<nums.size()-1;i++)
        {   
            depth[i]=(nums[i]-nums[i-1])*(nums[i+1]-nums[i])<0?1:0;
        }
        int count=0;
        for(int i=1;i<depth.size()-1;i++)
        {
            if(depth[i]==1)
                count++;
        }

        if(count>0)
        return count+2;
        else
        {
            if(nums[0]==nums[nums.size()-1])
            return 1;
            return 2;
        }
    }
};
//1 7 4 4 9 以上代码就无法通过了。没有考虑到平坡加上一个变化端点的情况
//思考打补丁，要不就得去重，很麻烦。要不就得在for循环里去重，但问题是没法直接continue跳过，重复会影响到前一个的计算逻辑。
//代码随想录的正解
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        int curDiff = 0; // 当前一对差值
        int preDiff = 0; // 前一对差值
        int result = 1;  // 记录峰值个数，序列默认序列最右边有一个峰值
        for (int i = 0; i < nums.size() - 1; i++) {
            curDiff = nums[i + 1] - nums[i];
            // 出现峰值
            if ((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) 
            {
                result++;
                preDiff = curDiff; // 注意这里，只在摆动变化的时候更新prediff，否则就错了
            }
        }
        return result;
    }
};


//动态规划
class Solution {
public:
    int dp[1005][2];
    int wiggleMaxLength(vector<int>& nums) 
    {
//dp[i][0]：以 nums[i] 结尾，并且最后一段趋势为“上升” 的最长摆动子序列长度
//dp[i][1]：以 nums[i] 结尾，并且最后一段趋势为“下降” 的最长摆动子序列长度

        memset(dp, 0, sizeof dp);
        dp[0][0] = dp[0][1] = 1;
        for (int i = 1; i < nums.size(); ++i) 
        {
            dp[i][0] = dp[i][1] = 1;
            for (int j = 0; j < i; ++j) 
            {
                if (nums[j] > nums[i]) dp[i][1] = max(dp[i][1], dp[j][0] + 1);
            }
            for (int j = 0; j < i; ++j) 
            {
                if (nums[j] < nums[i]) dp[i][0] = max(dp[i][0], dp[j][1] + 1);
            }
        }
        return max(dp[nums.size() - 1][0], dp[nums.size() - 1][1]);
    }
};
