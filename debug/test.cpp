#include <iostream>

using namespace std;

const int MAXN = 55;

int n, ans;
int w[MAXN];
int up[MAXN], down[MAXN];   // 上升子序列, 下降子序列

void dfs(int u, int su, int sd)
{
    if (su + sd >= ans) return;     
    if (u == n) { ans = su + sd; return; }

    int k = 0;
    while (k < su && up[k] >= q[u]) ++ k;
    int t = up[k];
    up[k] = q[u];
    if (k < su) dfs(u + 1, su, sd);
    
}

int main()
{
    while (cin >> n, n)
    {
        for (int i = 0; i < n; ++ i) cin >> w[i];
        ans = n;  // 最坏情况
        dfs(0, 0, 0);
        cout << ans << endl;
    }
    return 0;
}