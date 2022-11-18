// Dijkstar:
//		1) 初始化距离
//				- dis[1] = 0, dis[i] = 正无穷	
//				初始情况, 只有起始的距离是确定的(1~1的点距离为0)
// 
//		2) for in s (s:当前已确定最短距离的点)
//			  t <- 找到不再 s 中距离最近的点
//			  s <- t : 把 t 加入 s	 
//			  用 t 来更新其他点的距离
//			  t -> x : 当前 x 到 1 号点的距离是否可以换做 t 到 1 号点的距离更新 -> dis[x] 是否大于 dis[t] + w(权重) 
//			  t 出去的所有边组成的路径是否可以更新其他点
// 
// 用确定的点来更新待定点的最短距离
// 如果 n 是 10^5 两层循环就是 10^10, 就会超时
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

// n:点
// m:边
// 稠密图
const int N = 510;
int n, m;
int g[N][N];
int dist[N]; // 从 1 号点走到每号点, 目前已经更新过的最短距离, 还可以再被别的点更新
bool st[N];  // 每个点的最短路径是否已经确定

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;            // 1 号点到 1 号点距离为 0

    // 一共有 n 个点, 迭代 n 次
    for (int i = 0; i < n; ++ i )
    {
        int t = -1;         // 将t设置为-1 因为Dijkstra算法适用于不存在负权边的图

        // 每次迭代的过程中都先找到当前未确定的最短距离的点中距离最短的点
        // 枚举每个点是否找到最小值, 将 t 更新成还没有找到最小值(当前)的点
        for (int j = 1; j <= n; ++ j )
            if (!st[j] && (t == -1 || dist[t] > dist[j])) // 如果 0~t > 0~j 的距离(当前 t 不是最短的) 就把 t 更新成 j
                t = j;                                    // t 更新成 j 再去确定该点走过, 找到还没有形成最短路径的点
    
        st[t] = true;       // t 已经确定为最
        
        // 选出来的 t 去更新到其他点的更短距离, j 代表 0~j 号点的距离
        for (int j = 1; j <= n; ++ j )
            dist[j] = min(dist[j], dist[t] + g[t][j]);
    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}


// 有向图
// 
//   2
// 1 -> 2 
//  \   | 1 
// 4 \  v
//     3
// 
//   1 2 3
// 1 0 2 4 
// 2 2 0 1
// 3 4 1 0
int main()
{
    scanf("%d%d", &n, &m);

    // memset(g, 0x3f, sizeof g);
    // 初始化每个点到每个点的距离
    for (int i = 1; i <= n; ++ i ) 
        for (int j = 1; j <= n; ++ j )
            if (i == j) g[i][j] = 0;
            else g[i][j] = INF;

    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = min(g[a][b], c);          // a 和 b 之间可能存在多条边, 保留长度最短的边   
    }
    int t = dijkstra();
    printf("%d\n", t);
    return 0;
}