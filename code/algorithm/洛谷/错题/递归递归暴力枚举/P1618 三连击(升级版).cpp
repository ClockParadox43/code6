#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int a, b, c;
bool st[10] = { 0 };
int tmp[10] = { 0 };
bool ans = false;

// 将数组拆分成 3 个数
int cons(int m)
{
    // 判断起始位置末尾位置(方程代入下)
    // 每组有 3 个
    // m = 1
    // 3m + ? = 1;
    //       ? = 1-3 = -2   
    // 3m = 3
    //  m = 1
    int sum = 0;
    for (int i = 3 * m - 2; i <= 3 * m; i++)
    {
        sum *= 10;
        sum += tmp[i];
    }
    return sum;
}

// 记录一个 sum, sum 不能超过 n
void dfs(int u)
{
    // //当n=10时x数组数字存满, 开始判断将比值同时扩大 a 倍数看看是否相等(比值的逆运算)
    if (u == 10 && cons(1) * b == cons(2) * a && cons(1) * c == cons(3) * a)
    {
        cout << cons(1) << " " << cons(2) << " " << cons(3) << endl;
        ans = true;
        return;
    }

    for (int i = 1; i <= 9; i++)
    {
        if (!st[i])
        {
            tmp[u] = i;   //存数字
            st[i] = 1;   //该数字被使用
            dfs(u + 1);  //下一位继续调用
            st[i] = 0;  //恢复
        }
    }
}

// 枚举所有 10 种数字组成和为 11 的数最大, 每个数最多 1~3
int main()
{
    scanf("%d%d%d", &a, &b, &c);
    dfs(1);     // 下标从 1 开始
    if (!ans) puts("No!!!");
    return 0;
}