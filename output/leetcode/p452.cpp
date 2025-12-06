class Solution 
{
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) 
    {
        return a[0] < b[0];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) 
    {
        if (points.size() == 0) 
        return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1; 
        for (int i = 1; i < points.size(); i++) 
        {
            if (points[i][0] > points[i - 1][1]) 
            {  // 气球i和气球i-1不挨着，注意这里不是>=
                result++; // 需要一支箭
            }
            else 
            {  // 气球i和气球i-1挨着
                points[i][1] = min(points[i - 1][1], points[i][1]); // 更新重叠气球最小右边界
            }//最关键一步！绝妙！
        }
        return result;
    }
};
//第二种解法，按右边缘排，从左到右看，一个子弹肯定是越往右打，越有可能打到更多的气球，反复贪心。
class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1]; // 按右边界排序
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1;
        int current_arrow_pos = points[0][1]; // 第一支箭射在第一个气球的右边缘

        for (int i = 1; i < points.size(); i++) {
            // 如果当前气球的左边 > 当前箭的位置
            // 说明这支箭射不到它，需要一支新箭
            if (points[i][0] > current_arrow_pos) {
                result++;
                current_arrow_pos = points[i][1]; // 新箭射在这个新气球的右边缘
            }
        }
        return result;
    }
};
