// #include <iostream>
// #include <cstdio>
// #include <cmath>
// #include <vector>
// using namespace std;
// class Solution {
// public:
//     int minSubArrayLen(int target, vector<int>& nums) 
//     {   
//         int i=0;
//         int result=INT16_MAX; 
//         int length=0;
//         int sum=0;
//         for(int j=0;j<nums.size();j++)
//         {sum+=nums[j];
//           while(sum>=target)
//           {
//             length=j-i+1;
//             result=result<length?result:length;
//             sum-=nums[i++];

//           }  
         

//         }
//          return result==INT16_MAX?0:result;
//     }
// };