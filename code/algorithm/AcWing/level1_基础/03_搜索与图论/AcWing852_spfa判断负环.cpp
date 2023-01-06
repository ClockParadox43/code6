// 思路2: https://konaeakira.github.io/
// 思路1:
// dist[x] : 1~x 点最短路径的长度
//  cnt[x] : 当前最短路边的个数
//
// dist[x] = dist[t] + w[i]
//  cnt[x] = cnt[t] + 1     从 1~t 的边数 + 1 条边就是 1~x 的边数
// 思路: 如果 cnt[x] >= n 一共有 n 个点, 那么就有 n-1 条边
//       这就代表着 一定有环, 因为是循环到队列为空, 所以所有边都会看一遍
//
// 比起求最短路, spfa 求最短路只是多级路了一个 cnt 数组来记录边的个数
// 只要边的个数 >= n, 那就存在负环
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;
const int N = 2010, M = 10010;

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int dist[N], cnt[N];
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

bool spfa()
{
    queue<int> q;       // 只存更小边
    
    // 并不是判断从 1 开始的负环, 可能 1 号点到不了某个负环
    // 所以将所有点都枚举一遍
    for (int i = 1; i <= n; ++ i )
    {
        st[i] = true;
        q.push(i);
    }
    
    while (q.size())
    {
        int t = q.front();
        q.pop();
        
        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;            // 统计边的个数

                if (cnt[j] >= n) return true;   // 只要边的个数 >= n, 就说明存在负环
                if (!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    return false;
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
    if (spfa()) puts("Yes");
    else puts("No");
    return 0;
}