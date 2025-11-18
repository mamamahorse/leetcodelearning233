class Solution :
    def maxSubArray(self,nums:List[int])-> int :
        maxsum=nums[0]
        cursum=0
        for num in nums:
            cursum=max(cursum+num,num)
            maxsum=max(maxsum,cursum)
        return maxsum