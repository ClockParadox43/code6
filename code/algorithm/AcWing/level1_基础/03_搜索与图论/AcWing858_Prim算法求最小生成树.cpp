// 类似问题: 铺设公路让城市之间可以相互联通, 问最小是多少
// 最小生成树: 构成生成树这些边加起来权值最小的
// 最小的成本让这个N个顶点联通
//
// 若连通图由n个顶点组成, 则其生成树必含有n个顶点和n - 1条边,
// 因此构造最小生成树的准则有三条
// 1) 只能使用图中权值最小的边来构造最小生成树
// 2) 只能使用恰好 n - 1 条边来连接图中的 n 个顶点
// 3) 用 n - 1 条边不能构成回路
//
// 构成最小生成树方法 : Kruskal和Prim算法, 这两个算法都采用了逐步求解额度贪心策略
// 
// 
// 当前的联通块
// st[]: 当前已经在联通块中的所有点
// 
// for (int i = 0; i < n; i ++ )
//     找到集合外距离最近的点 t=j -> t 是集合外距离集合最近的点
//     用 t 更新其他点到集合的距离
//     st[t] = true
// n次迭代之后所有点都已加入到S中
// 联系：Dijkstra算法是更新到起始点的距离, Prim是更新到集合S的距离
//
// 思路: 
// 这个点被定义成所有边当中到集合内部长度最小的边, 所以每次出来的都是最短边, 选的也是最短边
// 看下这个点连接到集合内部有多少条最短的边
// 
// 和 Dijkstra 区别: 一个每次出来的是最短路, 一个是最短边
// 1≤n≤500
// 1≤m≤105 稠密图用邻接矩阵存储

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 510, M = 100010, INF = 0x3f3f3f3f;

int n, m;
int g[N][N];
int dist[N];    // 集合内的距离 dist 代表的是 0~t 的距离
int st[N];      // 是否被加入过集合

int prim()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    int res = 0;        // 最小生成数所有边的长度集合 

    // 每次循环选出一个点加入到生成树
    // 如果还剩点就还有边, 每次加入 S 的边都是当前最小的, 连向最小边的点
    // 一旦选中就被标记了, 有几个点就循环几次, 每次选最小的
    for (int i = 0; i < n; ++ i)
    {
        int t = -1;
        for (int j = 1; j <= n; ++ j)                       // 每个点判断一次, 遍历出除集合外当前距离最小的点
            if (!st[j] && (t == -1 || dist[t] > dist[j])) 
                t = j;

        // i 不是第一次筛选, 并且 0~t 的距离是正无穷, 说明是孤立点, 说明图是不联通的, 也就不存在最小生成树
        if (i && dist[t] == INF) return INF;

        if (i) res += dist[t];  // 选择该点, 只要不是第一个点 dist 表示的就是当前这个点已经和另一个点连好了的
        st[t] = true;

        // 先加入答案再更新, 最小生成树中的答案不需要更新
        // 自环负权可能会更新到自己, 当 dist[j] = t 时, g[t][t] 可能会把自己更新的更小
        // 所以先加答案再更新(自己更小, res也会更小)

        // 枚举每条边, 是否可以用 t 将伸出去的边更新更小, 更新 j 到集合的距离
        for (int j = 1; j <= n; ++ j) dist[j] = min(dist[j], g[t][j]); 
    }
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    
    
    // for (int i = 1; i <= n; ++i )
    //    for (int j = 1; j <= n; ++ j)
    //       if (i == j) g[i][j] = 0;
    //       else g[i][j] = INF;
    
    memset(g, 0x3f, sizeof g);
    
    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = g[b][a] = min(g[a][b], c); // 如果有重边保留长度最小的那条边
    }
    
    int t = prim();
    
    if (t == INF) puts("impossible");
    else printf("%d\n", t);
    return 0;
}