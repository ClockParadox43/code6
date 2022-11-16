// 剪枝: 当一个方法存在矛盾, 直接停下, 不用在展开了
//       当前方案一定是不合法的, 就不用往下搜了

#include <iostream>

using namespace std;

const int N = 20;

int n;

char g[N][N];

// O(N!)
// udg[]: 正对角线, dg[]: 反对角线
// 对角线个数为 2N - 1
// n 行, m 列, n 条正对角线, n 条反对角线
bool col[N], dg[N], udg[N];

// 行+列=下对角线
// 行-列=上对角线
// 行-列+总列数(n)=去负号
// u-i+n 
void dfs(int u)
{
    // 当找到一组方案时:满足当前行数时
    if (u == n) 
    {
        for (int i = 0; i < n; ++ i ) puts(g[i]);
        puts("");
        return ;
    }

    // 枚举每一列
    for (int i = 0; i < n; ++ i )
    {
        if (!col[i] && !dg[i + u] && !udg[u - i + n])   // 剪枝:不是同行同列同对角线, 就能放皇后
        {
            g[u][i] = 'Q';
            col[i] = dg[i + u] = udg[u - i + n] = true;
            dfs(u + 1);
            // 恢复现场    
            col[i] = dg[i + u] = udg[u - i + n] = false;
            g[u][i] = '.';
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i )
        for (int j = 0; j < n; ++ j )
            g[i][j] = '.';
    dfs(0);

    return 0;
}