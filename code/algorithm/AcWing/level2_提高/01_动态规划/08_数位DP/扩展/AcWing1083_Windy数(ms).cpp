#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 35;

int l, r;
int a[N], al;
int f[N][N];

int dp(int pos, int st, int op)
{
    if (!pos) return 1;
    if (!op && ~f[pos][st]) return f[pos][st];
    int res = 0, maxx = op ? a[pos] : 9;
    for (int i = 0; i <= maxx; i ++ )
        if (abs(st - i) >= 2)
            res += dp(pos - 1, !i && st == -2 ? -2 : i, op && i == a[pos]);
    return op && st == -2 ? res : f[pos][st] = res;
}
int calc(int x)
{
    memset(f, -1, sizeof f); al = 0;
    for ( ; x; x /= 10) a[ ++ al] = x % 10;
    return dp(al, -2, 1);
}
int main()
{
    cin >> l >> r;
    cout << calc(r) - calc(l - 1) << endl;
    return 0;
}
