#include <iostream>
#include <cstring>
#include <cstring>

using namespace std;

const int N = 35;

int l, r;
int a[N], al;
int f[N][N];

// 同样是用 "前缀和" 思想, 转化为求一个 "前缀区间" 的 "数字个数", 直接套 数位DP 模板
// 为了保证 "从大到小" 的 "数位" 上的 "数字" 构成一个 "非下降" 的 "序列"
// 这里 "记忆化搜索" 的 参数st: 要记录 前一位数位的数字是什么

// 常用参数:
// 1.当前枚举到的数位 pos (搜索的深度)
// 2.前一位数(或是前几位数)的情况st (诸如 前一位是什么、前几位总和是多少、某个数出现了几次 等)
// 3.前几位的数字是否等于上界的前几位数字 op (0/1)op (0/1)(限制本次搜索的数位范围)
// 4.是否有前导零 lead (0/1)

// pos:从高位枚举到低位, 枚举深度
// st:记录的前一位数字
// op: 
int dp(int pos, int st, int op)
{
    if (!pos) return 1;
    if (!op && ~f[pos][st]) return f[pos][st];
    int res = 0, maxx = op ? a[pos] : 9;
    for (int i = st; i <= maxx; i ++ )
        res += dp(pos - 1, i, op && i == a[pos]);       // op:限制搜索范围, 如果op为将范围限制为当前深度的数, 否则, 将范围限制在最高上限9
    return op ? res : f[pos][st] = res;
}

int calc(int x)
{
    memset(f, -1, sizeof f); al = 0;
    for (; x; x /= 10) a[ ++ al] = x % 10;  // 至少有1位
    return dp(al, 0, 1);
}

int main()
{
    while (cin >> l >> r) 
        cout << calc(r) - calc(l - 1) << endl;
    return 0;
}