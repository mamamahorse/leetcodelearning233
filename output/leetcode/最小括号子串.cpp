#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    int n;
    string s;
    if (!(cin >> n >> s)) return 0;

    stack<int> st;
    // 放入 -1 作为初始参照物，处理起始位置就开始匹配的情况
    st.push(-1); 
    
    int max_len = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            // 遇到左括号，记录下标
            st.push(i);
        } else 
        {
            // 遇到右括号，尝试匹配
            st.pop();
            
            if (st.empty()) 
            {
                    st.push(i); //边界情况
            } else 
            {
                // 长度 = 当前下标 - 匹配完后剩下的栈顶下标
                max_len = max(max_len, i - st.top());
            }
        }
    }

    cout << max_len << endl;

    return 0;
}