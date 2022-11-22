// AcWing 851. spfa求最短路9641人打卡
// AcWing 852. spfa判断负环8956人打卡
// AcWing 858. Prim算法求最小生成树9251人打卡
// AcWing 860. 染色法判定二分图

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// 收集所有边, 每次选最小的就加生成树

const int N = 100010, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], idx;
int st[N];
int q[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int bfs(int u, int c)
{
    int hh = 0, tt = 0;
    q[0] = 1;

    while (hh <= tt)
    {
        int t = q[hh ++ ];
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (!st[j])
            {
                st[j] = 3 - c;
                q[ ++ tt] = j;
            }
            else if (st[j] == st[t]) return false;
        }
    }
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    while (m -- )
    {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }

    int flag = true;
    for (int i = 1; i <= n; ++ i )
        if (!bfs(i, 1))
        {
            flag = false;
            break;
        }   

    flag == true ? puts("Yes") : puts("No");
    return 0;
}