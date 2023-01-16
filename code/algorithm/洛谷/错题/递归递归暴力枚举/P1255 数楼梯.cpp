#include <iostream>

using namespace std;
const int MAXN = 5010;


// 加法: 要用高精度来做
// 高精度 + fib数列
// 思路大概是用数组 f[k][j] 来存储走 k 个阶梯所用的步
// 将答案按照行存储, 如果第 i 行超过 10, 就用高精度加法, 最后循环输出
int n;
int f[MAXN][MAXN];
int len = 1;

void hp(int k)//高精度加法，k来存阶数 
{
    int i;
    for (i = 1; i <= len; i++)
        f[k][i] = f[k - 1][i] + f[k - 2][i];//套用公式 
    for (i = 1; i <= len; i++)             //进位 
        if (f[k][i] >= 10)
        {
            f[k][i + 1] += f[k][i] / 10;
            f[k][i] = f[k][i] % 10;
            if (f[k][len + 1])len++;
        }
}
int main()
{
    int i;
    scanf("%d", &n);
    f[1][1] = 1; f[2][1] = 2;         //初始化 
    for (i = 3; i <= n; i++)              //从3开始避免越界 
        hp(i);
    for (i = len; i >= 1; i--)             //逆序输出 
        printf("%d", f[n][i]);
    return 0;
}
