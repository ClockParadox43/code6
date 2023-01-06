#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
#include <unordered_map>

using namespace std;

stack<int> num;
stack<char> op;

// 思想:优先级大或相等的为一组, 一对括号为一组 即 碰到优先级小的就结算 
// 用末尾的运算符操作末尾的两个数
void eval()
{
    auto b = num.top(); num.pop();
    auto a = num.top(); num.pop();
    auto c = op.top(); op.pop();
    int x;
    if (c == '+') x = a + b;
    else if (c == '-') x = a - b;
    else if (c == '*') x = a * b;
    else x = a / b;
    num.push(x);
}

int main()
{
    // 运算符优先级
    unordered_map<char, int> pr{ {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
    string str;
    cin >> str;
    for (int i = 0; i < str.size(); ++i)
    {
        auto c = str[i];
        if (isdigit(c))     // 如果当前是数字
        {
            int x = 0, j = i;
            // 字符串变数字
            while (j < str.size() && isdigit(str[j]))
                x = x * 10 + str[j++] - '0';
            i = j - 1;         // 出了花括号后, 因为还会 for 循环还会加一, 所以减 1
            num.push(x);       // 数字入栈
        }
        else if (c == '(') op.push(c);      // 如果是左括号直接将做括号入栈, 直到遇到右括号为止
        else if (c == ')')      // 找到收括号就结算当前数
        {
            while (op.top() != '(') eval();
            op.pop();           // 弹出左括号
        }
        else        // 出现运算符, 只要当前运算符优先级('+') 小于等于 栈顶运算符优先级('*')就能立刻 结算
        {
            // 如果栈是不空的 且 栈顶元素优先级大于等于当前元素的优先级 且栈顶不是左括号
            while (op.size() && op.top() != '(' && pr[op.top()] >= pr[c]) 
                eval();
            op.push(c);
        }
    }
    while (op.size()) eval();
    cout << num.top() << endl;

    return 0;
}