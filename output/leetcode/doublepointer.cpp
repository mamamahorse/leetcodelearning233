#include <cstdio>  
#include <vector>  
using namespace std;

int main() 
{
    vector<int> nums;
    int val;
    
    while (scanf("%d", &val) == 1) 
    {
        nums.push_back(val);
        char ch = getchar();
        if (ch == '\n') 
        {
            break;
        }
    }
    int target;
    scanf("%d", &target);
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) 
    {
        int sum = nums[left] + nums[right];

        if (sum == target) 
        {
            printf("%d %d\n", nums[left], nums[right]);
            
            left++;
            right--;
        } 
        else if (sum < target) 
        {
            left++;
        } 
        else 
        {
            right--;
        }
    }

    return 0;
}