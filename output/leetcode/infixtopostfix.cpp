#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cmath> 
using namespace std;

int precedence(char op)
 {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isRightAssociative(char op) 
{
    return op == '^';
}

bool shouldPop(char top, char current) 
{
    if (top == '(') return false;
    int topPrec = precedence(top);
    int currPrec = precedence(current);
    if (topPrec > currPrec) return true;
    if (topPrec == currPrec && !isRightAssociative(current)) 
    return true;
    return false; //一定要记得返回false。相当于其余情况都false
    //入栈的条件：要入栈的比栈内的优先级高，或者相等且右结合
    //若不是，则出栈pop
}//a ^ b ^ c 如果右结合则是a b c ^ ^
//左结合则是a b ^ c ^
vector<string> infixToPostfix(const string &expr) 
{
    vector<string> output;
    stack<char> st;
    for (char ch : expr) 
    {
            if (isdigit(ch)) 
            {
                output.push_back(string(1, ch));
            } 
        else if (ch == '(') 
        {
            st.push(ch);
        } 
        else if (ch == ')') 
        {
            while (!st.empty() && st.top() != '(') 
            {
                output.push_back(string(1, st.top()));
                st.pop();
            }
            st.pop(); 
        }
         else 
        { 

              while (!st.empty() && shouldPop(st.top(), ch)) 
            {
            output.push_back(string(1, st.top()));
            st.pop();
            }
    st.push(ch);
        }
    }
    while (!st.empty()) {
        output.push_back(string(1, st.top()));
        st.pop();
    }
    return output;
}

void evaluatePostfix(vector<string> postfix) {
    stack<int> st;

    for (size_t i = 0; i < postfix.size(); i++) 
    {
        if (i)
         cout << " ";
        cout << postfix[i];
    }
    cout << "\n";

    for (size_t i = 0; i < postfix.size(); i++) 
    {
        if (isdigit(postfix[i][0])) 
        {
            st.push(postfix[i][0] - '0');
        } 
        else 
        {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            int res;
            if (postfix[i] == "+") res = a + b;
            else if (postfix[i] == "-") res = a - b;
            else if (postfix[i] == "*") res = a * b;
            else if (postfix[i] == "/") res = a / b;
            else if (postfix[i] == "^") res = pow(a, b);
            st.push(res);

            postfix[i] = to_string(res);
            postfix.erase(postfix.begin() + (i - 2), postfix.begin() + i);
            i -= 2;

            for (size_t j = 0; j < postfix.size(); j++) {
                if (j) cout << " ";
                cout << postfix[j];
            }
            cout << "\n";
        }
    }
}

int main() {
    string expr;
    cin >> expr;

    vector<string> postfix = infixToPostfix(expr);
    evaluatePostfix(postfix);

    return 0;
}
