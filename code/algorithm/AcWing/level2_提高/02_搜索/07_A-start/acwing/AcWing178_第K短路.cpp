// 对比
// 求最短路问题: 当一个点能被更新成更小, 才会加进来
// 第 k 短路: 从 0 开始扩展, 当前所有可以扩展到的点要去全部加进来    
// 相当于暴搜, 因为可能性特别多所以非常适合 A* 算法
// 估计函数: 需要保证它小于等于真实的距离, 所以估计函数取的是从当前点到终点的最短距离
//           所以就是反向求从终点到每个点的最短距离, 相当于反向跑一遍 dijkstra
// 直观想法: 因为每次从堆顶弹出的是最小值, 所以弹出的第 k 个, 就是第 k 小的
// 
// ps:如果存在长度一样的路径, 那么第 k 次出列的终点的路径不是严格第 k 小, 此时加一个判重就行了
//    只有在第 i 次出列终点的距离与上次不同才更新
// 
// 蓝皮书中的错误:点最多会被弹出 k 次
//      因为 A* 算法中除了终点以外其余任何一个点, 当它从队列中被弹出它不一定是最小值
//      估计函数只是对于终点而言的, 除终点以外的任意点都不满足三角形不等式
//      因为 k = 1 时, 都不一定只弹出 1 次, 所以这个结论是错误的, 除了终点以外, 中间的点都不止更新 k 次
//
// 某个点弹出k次即第k小, 但是第k小不一定只被更新k次
// 
// 整体思路就是先求出预估值, 用预估值来进行排序可以减少时间复杂度
// 每次都求最短路, 
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, PII> PIII;
const int N = 1010, M = 200010;

int n, m, S, T, K; // S:起点, T:终点, K:边数
int h[N], rh[N], e[M], w[M], ne[M], idx;    // h[]:正向邻接表表头, rh[]:反向邻接表表头
int d[N], cnt[N];
bool st[N];

// h[]: a 有一条指向 b 的边   a->b->c 
// rh[]: b 有一条指向 a 的边  a<-b<-c
void add(int* h, int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

// 估计函数取的是从当前点到终点的最短距离
// 所以就是反向求从终点到每个点的最短距离, 相当于反向跑一遍 dijkstra
// 预估值是只针对终点
void dijkstra()
{
    priority_queue<PII, vector<PII>, greater<PII>> heap; heap.push({0, T}); // 终点
    memset(d, 0x3f, sizeof d);
    d[T] = 0;

    while (heap.size())
    {
        auto t = heap.top(); heap.pop();
        int ver = t.second;
        if (st[ver]) continue;
        st[ver] = true;

        for (int i = rh[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (d[j] > d[ver] + w[i])
            {
                d[j] = d[ver] + w[i];
                heap.push({d[j], j});
            }
        }
    }
}

// 根据预估值排序, 返回真实值
int a_star()
{
    // 谁的 d[u] + f[u] 更小, 谁出队列
    // 每一个点, 当前点到终点的距离和当前点到起点的距离
    // d[S]:起点的估计值,
    // 0:真实值
    // S:编号
    // S 的值应该很大, 对于 d[] 来说 T 才是 0
    priority_queue<PIII, vector<PIII>, greater<PIII>> heap; heap.push({d[S], {0, S}});
    while (heap.size())
    {
        auto t = heap.top(); heap.pop();
        // ver:当前点, dist:起点到当前点的值
        int ver = t.second.second, dist = t.second.first;
        cnt[ver] ++ ;   // 对应来到每个点的次数加一
        
        // 如果终点已经被访问过 k 次了 则此时的 ver 就是终点 T 返回真实值
        // 第一次搜到目标点后, 堆中还存在别的点到目标点的值, 和 BFS 不一样的时每次弹出的是最小点
        // 所以不存在什么队尾, 就看别的值可以搜到目标点几次
        if (cnt[T] == K) return dist;

        // 扩展所有边 将所有点全部加进来
        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            
            // 如果走到一个中间点都 cnt[j]>=K , 则说明 j 已经出队 k 次了, 且astar()并没有return distance,
            // 说明从 j 出发找不到第 K 短路(让终点出队K次)
            // 即继续让 j 入队的话依然无解
            // 那么就没必要让 j 继续入队了
            
            // first: dist是当前值 + w[i] + 估计值(dijkstra求出的当前点到终点的距离) -> 用来排序
            // second: dist + w[i]: 起点到当前点的距离, 对应 j 这个点   -> 用来计算估计值
            // w[i]: 是 dist 到 点j 的距离
            if (cnt[j] < K) heap.push({dist + w[i] + d[j], {dist + w[i], j}});
        }
    }
    return -1;
}

int main()
{
    scanf("%d%d", &n, &m);
    
    memset(h, -1, sizeof h);
    memset(rh, -1, sizeof rh);
    
    for (int i = 0; i < m; ++ i )
    {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(h, a, b, c);    // 建正边
        add(rh, b, a, c);   // 建反边
    }
    
    scanf("%d%d%d", &S, &T, &K);
    /*
    这里补充一下，为什么当S==T时，K++。
    当起点和终点相同时，K中隐含了一条长度为0的没有边的最短路，但这条路是不对的，因为起点和终点至少包含一条边，所以K++，排除掉长度为0的最短路。此外，K使得边不存在时astar不会返回0而是返回-1。
    参考测试用例：
    1 0
    1 1 1
    */
    if (S == T) K ++ ;
    
    dijkstra();
    printf("%d\n", a_star());
    return 0;
}