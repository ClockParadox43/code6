#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 35, INF = 0x3f3f3f3f;

int n;
int w[N];
int f[N][N], g[N][N];

int dp(int l, int r)
{
    if (~f[l][r]) return f[l][r];                    //记忆化搜索
    if (l == r) return g[l][r] = l, f[l][r] = w[l];  //题设只有一个节点时，分数就是权值
    if (l > r) return f[l][r] = 1;                   //题设空子树的分数为1
    int score = -INF;
    for (int root = l, t; root <= r; ++ root)
        if ((t = dp(l, root - 1) * dp(root + 1, r) + w[root]) > score)
            score = t, g[l][r] = root;
    return f[l][r] = score;
}
void dfs(int l, int r)
{
    if (l > r) return;
    cout << g[l][r] << " ";
    dfs(l, g[l][r] - 1);
    dfs(g[l][r] + 1, r);
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> w[i];
    memset(f, -1, sizeof f);
    cout << dp(1, n) << endl;
    dfs(1, n);
    return 0;
}
