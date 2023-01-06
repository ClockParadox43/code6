// bellman ford 很傻, 每次循环都要遍历每条边
// spfa 对此进行了优化, 用宽度优先搜索
// 1) 起点入队列 
//    dist[b] = min(dist[b], dist[a] + w)
//    只有 a 变小了 b 才会变小, a -> b 的权值更新
//    也就是说队列中存储的都是变小的节点
//
// while (q.size())
// {
//      t = q.front();
//      q.pop();
//      更新 t 的其他所有边, 也就是拿 t 来更新出边
//      只要 t 变小了, 所有以 t 为起点的边都会变小
// }
// 
// 相比 bellman ford, spfa 有选择的去更新别边
// 
// 基本思路: 我更新过谁, 我就拿谁来更新别人
// 一个点如果没有被更新成更小的话, 那么用这个点来更新别人
// 别人也不会变小, 只有这个点变小了, 后面的点才会变小
// 
// 队列中存的都是: 所有已经变小的点, 用来更新其他点的点
// 
// 虽然有负权, 但是有向, 因此不会死循环
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], w[N], idx;   
int dist[N];    // dist[i] 以 1 为起点的节点到节点 i 的距离
int st[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;   
}

int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    // queue 存储的是已经变小过的点
    queue<int> q;
    q.push(1);
    st[1] =  true;      // 防止队列中存储重复点
    
    // 为什么不会死循环, 每次队列中存储的是已经变小的点, 越来越小是有上限的
    while (q.size())
    {
        int t = q.front();
        q.pop();
        
        st[t] = false;  // 从队列中取出来之后该节点st被标记为false, 代表之后该节点如果发生更新可再次入队

        // 从该点出发遍历所有边
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            // w[i]:是 i->j 的权重
            // 如果 j 已经在队列, 但是, 另外一个点更新到 j
            // 此时 j 会被更新, 但是 j 不会重复入队列 
            if (dist[j] > dist[t] + w[i])       // 记录当前更短的边
            {
                dist[j] = dist[t]  + w[i];
                if (!st[j])                     // 当前已经加入队列的结点, 无需再次加入队列, 即便发生了更新也只用更新数值即可, 重复添加降低效率
                {                               // 这也说明了如果存在负权回路会变成死循环
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    if(dist[n]==0x3f3f3f3f) return -1;
    else return dist[n];
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    
    spfa();
    if (dist[n] == 0x3f3f3f3f) puts("impossible");
    else printf("%d\n", dist[n]);

    return 0;
}