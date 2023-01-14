#include <iostream>
#include <cstring>

using namespace std;
const int MAXN = 1005;

int n = 5;
int a[MAXN] = {4, 2, 3, 1, 5};
int dp[MAXN];

// 已 a[i] 为末尾的最长子序列的长度
int main()
{
    memset(dp, -1, sizeof dp);
    int ans = 0;
    for (int i = 0; i < n; ++ i)
    {
        dp[i] = 1;
        for (int j = 0; j < i; ++ j)
            if (a[j] < a[i])
                dp[i] = max(dp[j] + 1, dp[i]);
        ans = max(dp[i], ans);
    }
    
    printf("%d", ans);
    return 0;
}