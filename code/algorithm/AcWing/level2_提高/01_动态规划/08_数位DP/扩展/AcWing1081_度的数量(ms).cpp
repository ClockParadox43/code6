// 记忆化的f[i][j]代表的是不贴上界, 当前位置是i, 之前的数是j的情况下的合法方案. 
// 为什么要不贴上界(很多都没提)? 因为当前位置的limit无约束之后才能xjb选树, 如果紧贴上界的话, 后面的数就不能随便选了.
// 只有不贴上界, 这个f[i][j]才是可以复用的. 否则这个状态和后面的f[i][j]不具备一致性.

#include <iostream>
#include <cstring>

using namespace std;

const int N = 35;
int l, r, k, b;
int a[N], al;
int f[N][N]; // 当前位置是i, 之前的数是j的情况下的合法方案

// 当前枚举到的数位 pos (搜索的深度)
// 前一位数(或是前几位数)的情况st (诸如 前一位是什么, 前几位总和是多少, 某个数出现了几次 等)
// 前几位的数字是否等于上界的前几位数字op(0/1)(限制本次搜索的数位范围)
// 是否有前导零 lead (0/1)
int dp(int pos, int st, int op) // op: 1=, 0<
{
    // 枚举到最后一位数位, 是否恰有k个不同的1(也是递归的终止条件)
    if (!pos) return st == k;
    // 记忆化搜索, 前提是不贴着上界(可以枚举满这一位所有的数字)
    if (!op && ~f[pos][st]) return f[pos][st];
    // 01数位dp, 贴着上界时, 本轮能枚举的最大数就是上界数位的数字和1之间的最小值
    int res = 0, maxx = op ? min(a[pos], 1) : 1;
    for (int i = 0; i <= maxx; ++ i) // 最多只能填到1
    {
        if (st + i > k) continue;    // 大于k不符合条件, 过滤掉不符合条件的, st是前统计的1的个数
        res += dp(pos - 1, st + i, op && i == a[pos]); // op && i == a[pos]:
    }
    return op ? res : f[pos][st] = res;
}

int calc(int x)
{
    al = 0; memset(f, -1, sizeof f);    // 模板的必要初始化步骤
    while (x) a[ ++ al] = x % b, x /= b;// 把x按照进制分解到数组中, al 是最高位
    return dp(al, 0, 1);    
}

int main()
{
    cin >> l >> r >> k >> b;
    cout << calc(r) - calc(l - 1) << endl;
    return 0;
}