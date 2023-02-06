#include <iostream>
#include <cstring>

using namespace std;
const int N = 10010, M = N << 1, INF = 0x3f3f3f3f;

int n;
int h[N], e[M], w[M], ne[M], idx;
int d1[N], d2[N], up[N];
int s1[N], s2[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs_d(int u, int father)
{
    // d1[u] = d2[u] = -INF;    // 该题没有负权边, 可以不用初始化为负无穷
    for (int i = h[u]; ~ i; i = ne[i])
    {
        int t = e[i];
        if (t == father) continue;
        dfs_d(t, u);
        if (d1[t] + w[i] >= d1[u])
        {
            d2[u] = d1[u], s2[u] = s1[u];       // 次大值更新为最大值, 次大的u的孩子更新为最大的u的孩子
            d1[u] = d1[t] + w[i], s1[u] = t;    // 最大值更新为当前值, 最大值的u的孩子更新为当前孩子
        }
        else if (d1[t] + w[i] >= d2[u])
            d2[u] = d1[t] + w[i], s2[u] = t;
        
    }
}

void dfs_u(int u, int father)
{
    for (int i = h[u]; ~ i; i = ne[i])
    {
        int t = e[i];
        if (t == father) continue;
        if (s1[u] == t) up[t] = w[i] + max(up[u], d2[u]);   // 当 son_u = t, 用次大更新
        else up[t] = w[i] + max(up[u], d1[u]);  // 当 son_u != t, 用最大更新
        dfs_u(t, u);
    }
}

int main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; ++ i)
    {
        int a, b, c; cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }

    dfs_d(1, -1);
    dfs_u(1, -1);
    
    int res = INF;
    for (int i = 1; i <= n; i ++ ) 
        res = min(res, max(d1[i], up[i]));
    cout << res << endl;
    return 0;
}