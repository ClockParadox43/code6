#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1003, MAXM = 503, MAXS = 103;
const int INF = 0x3f3f3f3f;
int n, m, K;
int f[MAXM][MAXS];

// f[i][j] 表示体力为 i, 收集了 j 个精灵 用的最小的精灵球数量
// 倒过来想: 减去1个精灵, 就要加上花费精灵球的数量
// 我们想得到更多的精灵, 就要求最少的精灵球花费数量
int main()
{
    memset(f, 0x3f, sizeof f);  // 因为所求是精灵球数量最小所以初始化正无穷
    scanf("%d%d%d", &n, &m, &K);    // n 个球, m血量, K 个精灵
    f[0][0] = 0;
    for (int i = 1, w, v; i <= K; ++ i)
    {
        scanf("%d%d", &w, &v);  // w:球, v:血量
        for (int j = m; j >= v; -- j)       
            for (int k = K; k >= 1; -- k)   // 精灵
                if (f[j - v][k - 1] + w <= n) // 体积 和 价值 是互逆的 f[j-v][k-w] + 1 移项得 f[j-v][k-1]+w
                    f[j][k] = min(f[j][k], f[j - v][k - 1] + w);    // 这里 w 是价值
    }

    for (int k = K; ~k; -- k)
    {
        int p = INF; 
        for (int j = 0; j < m; ++ j)
            if (f[j][k] != INF && j < p)    // 如果血量小于临时的
                p = j;
        if (p != INF) { printf("%d %d\n", k, m - p); return 0; }
    }

    return 0;
}