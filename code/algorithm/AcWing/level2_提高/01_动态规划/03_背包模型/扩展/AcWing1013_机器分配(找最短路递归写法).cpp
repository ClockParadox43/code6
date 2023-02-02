#include <iostream>

using namespace std;

const int N = 20;

int n, m;
int w[N][N];
int f[N][N];
int path[N], cnt;

void dfs(int i, int j)
{
    if (!i) return;
    //寻找当前状态f[i][j]是从上述哪一个f[i-1][k]状态转移过来的
    for (int a = 0; a <= j; ++ a)
        if (f[i - 1][j - a] + w[i][a] == f[i][j])
        {
            path[cnt ++ ] = a;
            dfs(i - 1, j - a);
            return;
        }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            cin >> w[i][j];
    
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            for (int k = 0; k <= j; ++ k)
                f[i][j] = max(f[i][j], f[i - 1][j - k] + w[i][k]);
    cout << f[n][m] << endl;
    dfs(n, m);
    for (int i = cnt - 1, id = 1; i >= 0; ++ id, -- i)
        cout << id << ' ' << path[i] << endl;
    return 0;
}