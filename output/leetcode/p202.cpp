
// #include <unordered_set>
// #include <vector>
// #include <iostream>
// using  namespace std;
// class Solution
// {public:
//     int getsum(int num)
//     {
//        int sum =0;
//        while(num)
//        {sum+= (num%10)*(num%10);
//         num/=10;
//        }
//        return sum;
//     }
//     bool isHappy(int n)
//     {unordered_set<int> set;
//         while(1)
//         {int sum =getsum(n);
//         if(sum==1)
//         return true;
//         if(set.find(sum)!=set.end())
//         return false;
//         else
//         set.insert(sum);
//         n=sum;
//         }
        
//     }


// };