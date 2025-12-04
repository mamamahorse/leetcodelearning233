class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
    {
    int cursum=0;
    int min =INT_MAX;
    for(int i=0;i<gas.size();i++)
    {
        int rest=gas[i]-cost[i];
        cursum+=rest;
        if(cursum<min)
        {
            min=cursum;//不管如何先跑一圈，看中途有没有汽油为负的情况。
        }
    }
    if(cursum<0)//总和是负的，从哪出发都不行
    return -1;
    if(min>=0)
    return 0;
    for(int i=gas.size()-1;i>=0;i--)
    {

        int rest=gas[i]-cost[i];
        min+=rest;
        if(min>=0)
        return i;//从0开始不行，但总和大于0，从其他节点出发试试，注意题目要求只能沿着一个方向。

    }
    return -1;
        
    }
};  

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int curSum = 0;
        int totalSum = 0;
        int start = 0;
        for (int i = 0; i < gas.size(); i++) 
        {
            curSum += gas[i] - cost[i];
            totalSum += gas[i] - cost[i];
            if (curSum < 0) {   // 当前累加rest[i]和 curSum一旦小于0
                start = i + 1;  // 起始位置更新为i+1
                curSum = 0;     // curSum从0开始
            }
        }
        if (totalSum < 0) return -1; // 说明怎么走都不可能跑一圈了
        return start;
    }
};