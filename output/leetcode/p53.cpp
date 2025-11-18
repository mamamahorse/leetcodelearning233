class Solution
{
    public:
    struct sum
    {
        int lsum,rsum,msun,isum;
    };
    sum pushup(sum left,sum right)
    {
        sum res;
        res.lsum = max(left.lsum,left.isum + right.lsum);
        res.rsum = max(right.rsum,right.isum + left.rsum);
        res.isum = left.isum + right.isum;
        res.msun = max(max(left.msun,right.msun),left.rsum + right.lsum);
        return res;
    }                           
    sum build(vector<int>&nums,int l,int r)
    {
        if(l == r)
        {
            return {nums[l],nums[l],nums[l],nums[l]};
        }
        int mid = (l + r) >> 1;
        sum left = build(nums,l,mid);
        sum right = build(nums,mid + 1,r);
        return pushup(left,right);
    }
    int maxSubArray(vector<int>& nums)
    {
        sum res = build(nums,0,nums.size() - 1);
        return res.msun;
    }

};