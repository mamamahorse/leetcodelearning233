// #include <iostream>
// #include <cstdio>
// #include <cmath>
// #include <vector>
// using namespace std;
// class Solution {
// public:
//     int removeElement(vector<int>& nums, int val) 
//     {  int size =nums.size();
//         int count=0;
//         for(int i=0;i<size;i++)
//         {   if(val==nums[i])
//         {    count++;
//             for(int j=i;j<size-1;j++)
//             nums[j]=nums[j+1];
//             size--;
//         }
//           }
//         return count;
//     }
// };