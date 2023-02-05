#include <iostream>
#include <cstring>

using namespace std;

const int N = 210;
int f[N][N], n, w[N];

int dp(int l, int r)
{
    if(l + 1 == r) return 0;
    int &v = f[l][r];
    if( ~v ) return v;

    for (int k = l + 1; k < r; k ++ ) 
        v = max(v, dp(l, k) + dp(k, r) + w[l] * w[k] * w[r]);
    return v;
}

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; i ++ )
        scanf("%d", &w[i]), w[i + n] = w[i];

    memset(f, -1, sizeof f);
    int res = 0;
    for (int i = 1; i <= n; i ++ )
        res = max(res, dp(i, n + i));
    printf("%d\n", res);

    return 0;
}
