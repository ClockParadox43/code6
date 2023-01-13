// 错误原因: 当搜索到时不能立即返回, 该题需要看完整个棋盘
//           搜索到一个答案后就返回, 下一行就看不了了
//              - 可能棋子放完了, 并且来到了最后一列, 返回后就下不去了
//                那么我们选择该位置不放棋子
// DFS 要不漏
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
        ans++;
        return;
    }

    if (u == n) return;
    // 当前行放棋子
    for (int i = 0; i < n; ++i)
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
        for (int i = 0; i < n; ++i)
            scanf("%s", &g[i]);

        dfs(0, k);
        printf("%d\n", ans);
    }
    return 0;
}
