// 不恢复现场意味着系统帮我们来维护结点状态, 恢复现场意味着自己来维护结点的状态
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110;

int n;
char g[N][N];
int xa, ya, xb, yb;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
bool st[N][N];

bool dfs(int x, int y)
{
    if (g[x][y] == '#') return false; 
    if (x == xb && y == yb) return true;
    
    st[x][y] = true;
    
    for (int i = 0; i < 4; ++ i )
    {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a >= n || b < 0 || b >= n) continue;
        if (st[a][b]) continue;
        // if (g[a][b] == '#') continue;  
        // 错误原因: 如果(x,y)一上来就是 #, 也就是说出事情况就走不通
        //          因为只会判断周围的点, 所以这点会被忽略掉, 最多只会被其他格子扩展到的时候跳过
        //          所以 这段判断应该加在进入函数的时候, 空降到这个格子直接返回  
        if (dfs(a, b)) return true;
    }

    // 扩展的 4 个点都没有找到也会返回 false
    // 中途返回 false 只会不符合判断条件进入下一个循环
    // 返回 true 会一层层回返给外边, 最后一个 if 会触发一个连锁反应, 碰到 true 直接出去了 
    return false;
}

int main()
{
    int q; scanf("%d", &q);
    while (q -- )
    {
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i ) scanf("%s", g[i]);
        scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
        memset(st, 0, sizeof st);
        if (dfs(xa, ya)) puts("YES");
        else puts("NO");   
    }
    return 0;
}