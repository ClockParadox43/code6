// 思路
// 堆优化版的dijkstra是对朴素版dijkstra进行了优化, 在朴素版dijkstra中时间复杂度最高的寻找距离
// 最短的点O(n^2)可以使用最小堆优化
// 1) 一号点的距离初始化为零, 其他点初始化成无穷大
// 2) 将一号点放入堆中
// 3) 不断循环, 直到堆空. 每一次循环中执行的操作为:
//    弹出堆顶(与朴素版 dijkstra 找到 S 外距离最短的点相同, 并标记该点的最短路径已经确定)
//    用该点更新临界点的距离(找更小), 若更新成功就加入到堆中


#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1e6 + 10;

typedef pair<int, int> PII;

int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];    
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    // 因为是小根堆, 所以每次更新完邻点后, 最小的那个邻点会浮在面
    priority_queue<PII, vector<PII>, greater<PII>> heap; 

    // 这里heap中为什么要存pair呢, 首先小根堆是根据距离来排的, 所以有一个变量要是距离
    // 其次在从堆中拿出来的时候要知道知道这个点是哪个点, 不然怎么更新邻接点呢? 所以第二个变量要存点
    // 这个顺序不能倒，pair排序时是先根据first，再根据second，这里显然要根据距离排序
    heap.push({ 0, 1 }); 
    while (heap.size())
    {
        PII k = heap.top();     // 取不在集合S中距离最短的点
        heap.pop();
        int ver = k.second, distance = k.first;
        
        if (st[ver]) continue;
        st[ver] = true;

        // 遍历该点的所有的邻点
        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];                       // i 只是个下标, e 中在存的是 i 这个下标对应的点
            if (dist[j] > distance + w[i])      // 如果 0~j 的距离有更近的, 就更新
            {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main()
{
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    
    while (m -- )
    {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        add(x, y, c);
    }

    cout << dijkstra() << endl;
    return 0;
}