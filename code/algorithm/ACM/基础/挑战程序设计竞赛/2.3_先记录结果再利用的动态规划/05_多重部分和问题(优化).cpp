// 同样的复杂度通常能获得更多的信息, 在该问题中, 我们不光能求出能否得到目标的和数
// 同时把得到时 ai 这个数还剩下多少个计算出来, 这样就能减少时间复杂度
//
// dp[i+1][j]:用前 i 种数字加和得到 j 时第 i 种数最多能剩余多少个(不能加和得到 j 的情况下为 -1)
//            
// 

#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 105, MAXK = 100010;

int n = 3, K = 17;
int a[3] = {3, 5, 8};
int m[3] = {3, 2, 2};
int dp[MAXK];

int main()
{
    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j <= K; ++ j)
        {
            if (dp[j] >= 0)
                dp[j] = m[i];
            else if (j < a[i] || dp[j - a[i]] <= 0)
                dp[j] = -1;
            else    
                dp[j] = dp[j - a[i]] - 1;
        }
    
    if (dp[K] >= 0) puts("Yes");
    else puts("No");

    return 0;
}