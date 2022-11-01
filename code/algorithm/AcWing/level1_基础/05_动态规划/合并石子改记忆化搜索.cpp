#include <iostream>
#include <cstring>

using namespace std;

const int N = 310;

int n;
int a[N], s[N];
int f[N][N];

// 记忆化搜索, dp 记忆化搜索递归实现
int dp(int i, int j)
{
    if (i == j) return 0;           // 判断边界
    int& v = f[i][j];

    if (v != -1) return v;

    v = 1e8;

    for (int k = i; k <= j - 1; ++ k )
        v = min(v, dp(i, k) + dp(k + 1, j) + s[j] - s[i - 1]);
    
    return v;
}

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; ++ i )
    {
        scanf("%d", &a[i]);
        s[i] += s[i - 1] + a[i];
    }
    memset(f, -1, sizeof f);
    printf("%d", dp(1, n));
    return 0;
}