#include <iostream>
#include <cstring>
using namespace std;

const int N = 25;

int n, m;
char g[N][N];
bool st[N][N];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int dfs(int x, int y)
{
    if (g[x][y] == '#') return 0;
    int cnt = 1;
    
    st[x][y] = true;
    for (int i = 0; i < 4; ++ i )
    {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a >= n || b < 0 || b >= m) continue;
        if (st[a][b]) continue;
        cnt += dfs(a, b);
    }
    return cnt;
}

int main()
{
    while (cin >> m >> n, n || m)
    {
        int x = 0, y = 0;
        for (int i = 0; i < n; ++ i ) 
            for (int j = 0; j < m; ++ j )
            {
                cin >> g[i][j];
                if (g[i][j] == '@') 
                    x = i, y = j; 
            }
        memset(st, 0, sizeof st);
        cout << dfs(x, y) << endl;
    }
    return 0;
}