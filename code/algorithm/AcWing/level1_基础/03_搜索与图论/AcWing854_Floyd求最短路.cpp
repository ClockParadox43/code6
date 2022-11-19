/*
解题思路, 动态规划的思想
    假设节点序号是从 1 到 n
    假设 f[0][i][j] 是一个 n*n 的矩阵, 第 i 行第 j 列代表从 i 到 j 的权值, 如果 i 到 j 有边, 那么其值就为 c[i, j] (边ij的权值)
    如果没有边, 那么其值就为无穷大.

    f[k][i][j] 代表 (k 的取值范围是从 1 到 n), 在考虑了从 1 到 k 的节点作为中间经过的节点时, 从 i 到 j 的最短路径的长度.

    比如, f[1][i][j] 就代表了, 在考虑了 1 节点作为中间经过的节点时, 从 i 到 j 的最短路径的长度
    分析可知, f[1][i][j] 的值无非就是两种情况, 而现在需要分析的路径也无非两种情况，i=>j, i=>1=>j:
     1) f[0][i][j]: i=>j 这种路径的长度, 小于, i=>1=>j 这种路径的长度
     2) f[0][i][1] + f[0][1][j]: i=>1=>j 这种路径的长度, 小于, i=>j 这种路径的长度
    形式化说明如下:
    f[k][i][j]可以从两种情况转移而来: 
     1) 从 f[k−1][i][j] 转移而来, 表示 i 到 j 的最短路径不经过 k 这个节点
     2) 从 f[k−1][i][k] + f[k−1][k][j] 转移而来, 表示 i 到 j 的最短路径经过k这个节点

    总结就是: f[k][i][j] = min(f[k−1][i][j], f[k−1][i][k] + f[k−1][k][j])
    从总结上来看, 发现 f[k] 只可能与 f[k−1] 有关.


    f[k][i][j] = min(f[k−1][i][j], f[k−1][i][k] + f[k−1][k][j])
    由此公式可得 f[k][i][k] = f[k-1][i][k], f[k][k][j] = f[k-1][k][j]  ps: k不可能是 (i, k) 或者 (k, j) 的中间节点
    所以 f[k][i][j] = min(f[k−1][i][j], f[k][i][k] + f[k][k][j])
    所以去掉最外层循环, f[i][j] = min(f[i][j], f[i][k] + f[k][j])
*/

// 笔记: 必须经过 k 这个点就代表其实还没有到 k 这个点, 那么依赖的就是 k-1, f[k-1][i][j], 就表示没有经过 k 这个点的状态, 
//       然后和必须经过 k 这个点的状态做比较即 f[k-1][i][k] + f[k-1][k][j]
//       
//      来到下面一层格子时, f[k - 1][i][j] 状态应该是从上面照抄下来的所以 f[k - 1][i][j] = f[k][i][j]
//      f[k][i][k] = f[k-1][i][k], f[k][k][j] = f[k-1][k][j]

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int N = 210, INF = 1e9;
int d[N][N];

int n, m, q;


// dp[k][i][j]: 从 i 这个点出发达只经过 1~k 这些中间点到达 j 的最短距离
void floyd()
{
    for (int k = 1; k <= n; ++ k )  
        for (int i = 1; i <= n; ++ i )  
            for (int j = 1; j <= n; ++ j )
                d[i][j] =  min(d[i][j], d[i][k] + d[k][j]);
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 0; i <= n; ++ i )
    {
        for (int j = 0; j <= n; ++ j )  
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;
    }

    while (m -- )
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        d[a][b] = min(d[a][b], w);  // 有重边那就选一条最短的
    }

    foldy();

    while (q -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if (d[a][b] > INF / 2) puts("impossible");
        else printf("%d\n", d[a][b]); 
    }

    return 0;
}