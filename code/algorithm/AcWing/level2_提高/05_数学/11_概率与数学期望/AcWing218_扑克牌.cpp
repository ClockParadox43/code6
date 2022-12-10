#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010, M = 200010;

int n, m;
int h[N], e[M], ne[M], w[M], idx;  // 邻接表
int dout[N];    // 每个点的出度
double f[N];    // 递推公式

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++ ;
}

double dp(int u)
{
    if (f[u] >= 0) return f[u];     // 记忆化搜索
    // if (u == n) return f[u] = 0  // n 号点一定是没有出边的所以不用特判

    f[u] = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];       // j 是 i 的孩子
        f[u] += (w[i] + dp(j)) / dout[u];   // 
    }
    return f[u];
}   

int main()
{
    scanf("%d%d", &n, &m);  // n 个点, m 条边
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++ i )
    {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);   // a -> b, 权值为 c
        add(a, b, c);
        dout[a] ++ ;    // a 有一条指向 b 的边, a 的出边个数加一
    }
    memset(f, -1, sizeof f);
    printf("%.2lf\n", dp(1));
    return 0;
}