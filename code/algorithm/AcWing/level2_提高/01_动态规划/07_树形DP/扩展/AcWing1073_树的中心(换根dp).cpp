#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010, M = N << 1, INF = 0x3f3f3f3f;

int n;
int h[N], e[M], w[M], ne[M], idx;
int d1[N], d2[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int dfs(int u, int father)
{
    d1[u] = d2[u] = 0;
    for (int i = h[u]; ~ i; i = ne[i])
    {
        int t = e[i];
        if (t == father) continue;
        int dist = dfs(t, u) + w[i];
        if (dist >= d1[u]) d2[u] = d1[u], d1[u] = dist;
        else if (dist > d2[u]) d2[u] = dist;
    }
    return d1[u];
}

int main()
{
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for (int i = 1; i < n; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    int res = INF;
    for (int i = 1; i <= n; i ++ ) res = min(res, dfs(i, -1));
    printf("%d\n", res);
    return 0;
}
