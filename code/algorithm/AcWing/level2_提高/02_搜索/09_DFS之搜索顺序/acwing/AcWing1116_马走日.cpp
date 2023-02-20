#include <iostream>

using namespace std;

const int N = 14;

int walk[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, 
                  {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};
int T, ans;
int n, m, sx, sy;
bool st[N][N];

void dfs(int x, int y, int cnt)
{
    if (cnt == n * m)
    {
        ans ++ ;
        return;
    }

    st[x][y] = true;
    for (int i = 0; i < 8; ++ i)
    {
        int dx = x + walk[i][0], dy = y + walk[i][1];
        if (dx < 0 || dx >= n || dy < 0 || dy >= m) continue;
        if (st[dx][dy]) continue;
        dfs(dx, dy, cnt + 1);
        // st[dx][dy] = false; 这么写是错的
    }
    st[x][y] = false;
}

int main()
{
    cin >> T;
    while (T -- )
    {
        ans = 0;
        cin >> n >> m >> sx >> sy;
        dfs(sx, sy, 1);
        cout << ans << endl;
    }
    return 0;
}