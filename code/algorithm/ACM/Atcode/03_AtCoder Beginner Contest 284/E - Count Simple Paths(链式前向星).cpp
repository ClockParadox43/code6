// 题目大意:
// 给定一个N个顶点, M条边的无向图. 
// 求从点1开始, 简单路径(没有重复顶点的路径)的数量K
// 答案取 min(K,1×10^6)

#include <iostream>
#include <cstring>

using namespace std;

const int N = 2e5 + 10, M = 2 * N;

int h[N], e[M], ne[M], idx;
bool st[N];
int ans = 1;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u)
{
    if (ans >= 1e6)
    {
        cout << 1000000 << endl;
        exit(0);
    }
    st[u] = true;
    for (int i = h[u]; ~ i; i = ne[i])
        if (!st[e[i]])
        {
            ans ++ ;
            dfs(e[i]);
            st[e[i]] = false;
        }
}

int main()
{
    int n, m;
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int a, b; cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    dfs(1);
    cout << ans << endl;
    return 0;
}