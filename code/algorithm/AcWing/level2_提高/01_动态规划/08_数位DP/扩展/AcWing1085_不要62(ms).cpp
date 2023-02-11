#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 35;

int l, r;
int a[N], al;
int f[N][N];
// f存储在没有贴合上界的情况下, 从第i位开始, 前一位是否是6的方案数
// 因为f是没有贴合上界的情况下, 即剩下i位可以从00…00~99…99随便填, 所以无论数a[]是多少都可以适用

int dp(int pos, int st, int op)
{
    if (!pos) return 1;
    if (!op && ~f[pos][st]) return f[pos][st];
    int res = 0, maxx = op ? a[pos] : 9;    // f是没有贴合上界的情况下，即!op
    for (int i = 0; i <= maxx; i ++ )
        if (i != 4 && (st != 6 || i != 2))  // 判断是否符合条件
            res += dp(pos - 1, st == -1 && !i ? -1 : i, op && i == a[pos]);
    return op && st == -1 ? res : f[pos][st] = res;  // f是没有贴合上界的情况下，即!op
}

int calc(int x)
{
    memset(f, -1, sizeof f); al = 0;
    for ( ; x; x /= 10) a[ ++ al] = x % 10;
    return dp(al, -1, 1);
}

int main()
{
    while (cin >> l >> r, l || r)
    {
        cout << calc(r) - calc(l - 1) << endl;
    }
    return 0;
}
