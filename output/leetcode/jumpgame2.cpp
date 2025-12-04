class Solution {
public:
    int jump(vector<int>& nums) 
    {
        if (nums.size() < 2) return 0; 
        
        int jumps = 0;      
        int curEnd = 0;     
        int maxPos = 0;     
        for (int i = 0; i < nums.size() - 1; i++) 
        {
            
            maxPos = max(maxPos, i + nums[i]);

            if (i == curEnd) 
            {
                jumps++;       
                curEnd = maxPos; 
            }
        }
        return jumps;
    }
};