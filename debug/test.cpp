#include <iostream>

using namespace std;
const int MAXN = 10;

int n, k, ans;
char g[MAXN][MAXN];
bool col[MAXN];

// u:代表来到当前行
void dfs(int u, int rest)
{
    if (rest == 0) 
    {
        ans ++ ;
        return;
    }

    // 当前行放棋子
    for (int i = 0; i < n; ++ i)
        if (!col[i] && g[u][i] == '#')
        {
            col[i] = true;
            dfs(u + 1, rest - 1);
            col[i] = false;
        }
    
    // 当前行不放置棋子/不能放置棋子
    dfs(u + 1, rest);
}

int main()
{
    while (~scanf("%d%d", &n, &k) && (n != -1 && k != -1))
    {
        ans = 0;
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; + j) 
                scanf("%c", &g[i][j]);
        
        dfs(0, k);
        printf("%d\n", ans);
    }
    return 0;
}