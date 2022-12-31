#include <iostream>
#include <cstring>

using namespace std;

bool a[1005][1005];

int ans; 

int main()
{
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    memset(a, 0, sizeof a);

    for (int i = 0; i < n; ++ i )
        for (int j = 1; j <= m; ++ j )
        {
            int x; cin >> x;        // 第 x 天有空
            a[x][j] = 1;            // 重点!(忽略了很多没用的信息) => 第 x 天 在 第 j 个有空的日子
        }

    
    // 枚举所有日子, 枚举第 i 天分别在哪些个日子有空

    for (int i = 1; i <= k; ++ i )      // 枚举所有日子
    {
        int ans = 0;
        for (int j = 1; j <= m; ++ j )  // 枚举恰好有空的日子
            if (a[i][j]) ++ ans;
        cout << ans << " ";
    }
    
    return 0;
}