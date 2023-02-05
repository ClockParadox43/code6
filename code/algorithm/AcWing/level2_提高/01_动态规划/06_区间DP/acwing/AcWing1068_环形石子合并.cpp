
#include <iostream>
#include <cstring>

using namespace std;

const int N = 410, INF = 0x3f3f3f3f;      // 开两倍的空间

int n;
int s[N], w[N];
int f[N][N], g[N][N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> w[i];
        w[i + n] = w[i];       // 预处理出两倍的长度
    }

    // 预处理前缀和
    for (int i = 1; i <= 2 * n; ++ i) s[i] = s[i - 1] + w[i];
    
    memset(f, 0x3f, sizeof f);      // 求最大值预处理出最小值
    memset(g, 0xcf, sizeof g);      // 求最小值预处理出最大值

    // ps:这里的len不用循环到2n, 因为我们需要的只是长度为n的左端点
    for (int len = 1; len <= n; ++ len)
        for (int l = 1; l + len - 1 <= 2 * n; ++ l)
        {
            int r = l + len - 1;       // 自动获得右端点
            if (len == 1) f[l][r] = g[l][r] = 0;
            else 
            {
                // 枚举分解分界点, 之前合并的代价加上当前合并的代价
                for (int k = l; k < r; ++ k)
                {
                    f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
                    g[l][r] = max(g[l][r], g[l][k] + g[k + 1][r] + s[r] - s[l - 1]);
                }
            }
        }
    // 目标状态中找出方案
    // 固定住右端点, 枚举左端点, 求最值
    int minv = INF, maxv = -INF;
    for (int i = 1; i <= n; ++ i)
    {
        minv = min(minv, f[i][i + n - 1]);
        maxv = max(maxv, g[i][i + n - 1]);
    }
    cout << minv << endl << maxv << endl;
    return 0;
}