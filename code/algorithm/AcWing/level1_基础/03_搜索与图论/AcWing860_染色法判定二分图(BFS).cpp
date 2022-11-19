// bfs版本
// 代码思路
//    1) 颜色 1 和 2 表示不同颜色, 0 表示 未染色
//    2) 定义 queue 是存 PII, 表示 <点编号, 颜色>
//    3) 同理, 遍历所有点, 将未染色的点都进行bfs
//    4) 队列初始化将第 i 个点入队, 默认颜色可以是 1 或 2
//          while (队列不空)
//          每次获取队头 t, 并遍历队头 t 的所有邻边
//              - 若邻边的点未染色则染上与队头 t 相反的颜色, 并添加到队列
//              - 若邻边的点已经染色且与队头 t 的颜色相同, 则返回 false
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10, M = 2e5 + 10;
typedef pair<int, int> PII;

int e[M], ne[M], h[N], idx;
int n, m;
int st[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

bool bfs(int u)
{
    int hh = 0, tt = 0;
    PII q[N];
    q[0] = {u, 1};
    st[u] = 1;

    while(hh <= tt)
    {
        auto t = q[hh ++];
        int ver = t.first, c = t.second;

        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(!st[j]) 
            {
                st[j] = 3 - c;
                q[++ tt] = {j, 3 - c};
            }
            else if(st[j] == c) return false; // 如果该层的点和队头是一种颜色返回 false
        }
    }

    return true;
}

int main()
{
    scanf("%d%d", &n, &m);

    memset(h, -1, sizeof h);
    while(m --)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }

    int flag = true;
    for(int i = 1; i <= n; i ++) 
    {
        if (!st[i])
            if(!bfs(i))
            {
                flag = false;
                break;
            }
    }

    if (flag) puts("Yes");
    else puts("No");
    return 0;
}