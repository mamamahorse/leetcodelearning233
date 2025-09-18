// #include <iostream>
// #include <cstdio>
// #include <cmath>
// #include <vector>
// using namespace std;

// class Solution {
// public:
//     vector<vector<int>> generateMatrix(int n) 
//     {
//       vector<vector<int>> r(n,vector<int>(n,0));
//       int startx=0;
//       int starty=0;
//       int mid=n/2;
//       int loop=n/2;
//       int count=1;
//       int offset=1;
//       while(loop--)
//       { int i=startx;
//         int j=starty;
//         for(;j<n-offset;j++)
//         r[i][j]=count++;
//         for(;i<n-offset;i++)
//         r[i][j]=count++;
//          for(;j>starty;j--)
//           r[i][j]=count++;
//            for(;i>startx;i--)
//           r[i][j]=count++;
//         offset++;
//         startx++;
//         starty++;

//       }
//                 if(n%2)
//           r[mid][mid]=count;
//           return r;
//     }
// };