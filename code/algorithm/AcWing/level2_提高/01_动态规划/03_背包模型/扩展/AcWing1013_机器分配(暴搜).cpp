#include <iostream>
#define N 11
#define M 16

using namespace std;

int w[N][M], n, m;
int cnt[N], ans;
int ans_cnt[N];

// 第num个公司, 总盈利, 剩余设备
void dfs(int num, int sum, int rest)
{
    if (num == n)   // 没有公司可以枚举了
    {
        sum += w[n][rest];     // 把剩下的设备分配给第n个公司
        cnt[n] = rest;         // 记录路径, 剩下的设备分配给第n台设备
        if (sum > ans)        // 如果有更好的方案
        {
            ans = sum;
            for (int i = 1; i <= n; ++ i) 
                ans_cnt[i] = cnt[i];
        }
        return;
    }
    for (int i = 0; i <= rest; ++ i)
    {
        cnt[num] = i;   // 为第num个公司分配i个设备
        dfs(num + 1, sum + w[num][i], rest - i);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            cin >> w[i][j];
    dfs(1, 0, m);
    cout << ans << endl;
    for (int i = 1; i <= n; ++ i) 
        cout << i << ' ' << ans_cnt[i] << endl;
    return 0;
}