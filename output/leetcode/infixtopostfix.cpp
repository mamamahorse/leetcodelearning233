#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <cctype>

using namespace std;

// === 辅助函数区 ===

// 获取运算符优先级
int getPrecedence(const string& op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

// 判断是否为右结合运算符
bool isRightAssociative(const string& op) {
    return op == "^";
}

// 判断是否是运算符
bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

// 执行单次计算
int calculate(int a, int b, const string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b; // 注意：这里未处理除以0的情况
    if (op == "^") return pow(a, b);
    return 0;
}

// === 核心逻辑区 ===

// 中缀表达式转后缀表达式
vector<string> infixToPostfix(const string &expr) {
    vector<string> output;
    stack<string> ops;

    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];

        // 1. 处理数字 (支持多位数)
        if (isdigit(ch)) {
            string num(1, ch);
            // 如果下一位还是数字，拼接起来
            while (i + 1 < expr.length() && isdigit(expr[i + 1])) {
                num += expr[++i];
            }
            output.push_back(num);
        }
        // 2. 处理左括号
        else if (ch == '(') 
        {
            ops.push("(");
        }
        // 3. 处理右括号
        else if (ch == ')') 
        {
            while (!ops.empty() && ops.top() != "(") 
            {
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop(); // 弹出左括号
        }
        // 4. 处理运算符
        else if (!isspace(ch)) { // 忽略空格，处理运算符
            string curOp(1, ch);
            while (!ops.empty() && ops.top() != "(") {
                string topOp = ops.top();
                int curPrec = getPrecedence(curOp);
                int topPrec = getPrecedence(topOp);

                // 弹出栈顶元素的条件：
                // 栈顶优先级更高，或者优先级相等且当前操作符是左结合
                if (topPrec > curPrec || (topPrec == curPrec && !isRightAssociative(curOp))) {
                    output.push_back(topOp);
                    ops.pop();
                } else {
                    break;
                }
            }
            ops.push(curOp);
        }
    }

    // 将栈中剩余的运算符全部输出
    while (!ops.empty()) {
        output.push_back(ops.top());
        ops.pop();
    }
    return output;
}

// 打印当前的表达式列表
void printStep(const vector<string>& tokens) {
    for (size_t i = 0; i < tokens.size(); i++) {
        if (i > 0) cout << " ";
        cout << tokens[i];
    }
    cout << endl;
}

// 后缀表达式求值 (带步骤显示)
void evaluatePostfixWithSteps(vector<string> postfix) {
    // 先打印初始状态
    printStep(postfix);

    // 我们需要通过不断修改 postfix 数组来模拟“规约”过程
    // 为了安全地在遍历中删除元素，我们使用 while 循环手动控制索引
    size_t i = 0;
    while (i < postfix.size()) {
        // 如果遇到运算符，进行计算
        if (isOperator(postfix[i])) {
            // 获取操作数（运算符前面的两个数）
            // 注意：因为是后缀，顺序是 ... a b op ...
            int b = stoi(postfix[i - 1]);
            int a = stoi(postfix[i - 2]);
            string op = postfix[i];

            int res = calculate(a, b, op);

            // 修改 vector：用结果替换 "a b op" 这一段
            // 1. 将运算符位置的值改为计算结果
            postfix[i] = to_string(res);
            
            // 2. 删除运算符前面的两个操作数
            // erase(start, end) 删除范围是 [start, end)
            // 我们要删除 i-2 和 i-1 位置的元素
            postfix.erase(postfix.begin() + i - 2, postfix.begin() + i);

            // 3. 打印当前步骤
            printStep(postfix);

            // 4. 调整索引：
            // 因为删除了2个元素，原本在 i 位置的新结果现在跑到了 i-2 的位置
            // 下一次循环应该从这个新结果的后面继续检查，所以索引回退
            i -= 2; 
        }
        i++;
    }
}

int main() {
    string expr;
    // 建议使用 getline 以支持包含空格的输入，虽然题目样例可能没有空格
    if (getline(cin, expr)) {
        vector<string> postfix = infixToPostfix(expr);
        evaluatePostfixWithSteps(postfix);
    }
    return 0;
}