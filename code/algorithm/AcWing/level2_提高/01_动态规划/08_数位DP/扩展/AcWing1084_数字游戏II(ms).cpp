#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 35, M = 110;

int l, r, n;
int a[N], al;
int f[N][M];

int dp(int pos, int st, int op)
{
    if (!pos) return !(st % n);
    if (!op && ~f[pos][st]) return f[pos][st];
    int res = 0, maxx = op ? a[pos] : 9;
    for (int i = 0; i <= maxx; i ++ )
        res += dp(pos - 1, st + i, op && i == a[pos]);
    return op ? res : f[pos][st] = res;
}
int calc(int x)
{
    memset(f, -1, sizeof f); al = 0;
    for ( ; x; x /= 10) a[ ++ al] = x % 10;
    return dp(al, 0, 1);
}
int main()
{
    while (cin >> l >> r >> n)
    {
        cout << calc(r) - calc(l - 1) << endl;
    }
    return 0;
}