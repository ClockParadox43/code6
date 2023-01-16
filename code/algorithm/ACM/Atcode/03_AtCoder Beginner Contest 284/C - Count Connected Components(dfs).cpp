#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int N = 210, M = 1e5;
int h[N], e[M], ne[M], idx;
bool st[N];
int ans;

void add(int x, int y)
{
    e[idx] = y, ne[idx] = h[x], h[x] = idx ++;
}

void dfs(int u)
{
    if (st[u]) return;

    st[u] = true;
    for (int i = h[u]; i != -1; i = ne[i])
        if (!st[e[i]]) dfs(e[i]);
}
int main()
{
    memset(h, -1, sizeof h);
    int n, m;
    cin >> n >> m;
    while(m -- )
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }

    // 建好图后, n 个点遍历 n 遍, 每次 dfs 都能遍历到自己所有孩子, 将它们标记为 true
    for (int i = 1; i <= n; ++ i)
        if (!st[i])
        {
            ans ++ ;
            dfs(i);
        }

    cout << ans << endl;
    return 0;
}
