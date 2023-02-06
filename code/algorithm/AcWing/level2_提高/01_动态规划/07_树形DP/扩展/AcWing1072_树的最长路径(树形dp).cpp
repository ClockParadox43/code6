#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e4 + 10;

int n, ans;
int h[N], e[2 * N], w[2 * N], ne[2 * N],idx; 
int f[2][N];

// f[1/2][u]:当前点到叶子的最大距离和次大距离
// 那么答案就是 f[0][u] + f[1][u]
void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int father)
{
    for (int i = h[u]; ~i ; i = ne[i])
    {
        int t = e[i];
        if (t == father) continue;
        dfs(t, u);
        if (f[0][t] + w[i] > f[0][u]) 
            f[1][u] = f[0][u], f[0][u] = f[0][t] + w[i];
        else if (f[0][t] + w[i] > f[1][u]) 
            f[1][u] = f[0][t] + w[i];
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
    dfs(1, -1);
    
    int res = 0;
    for(int i = 1; i <= n; ++ i)   // 遍历 n 个点选出经过点i的最大路径和
        res = max(f[0][i] + f[1][i], res);
    
    cout << res << endl;
    return 0;
}