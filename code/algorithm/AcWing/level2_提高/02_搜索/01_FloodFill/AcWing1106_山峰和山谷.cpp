// 这里我们暴搜所有一个点之间所有高度相等的点, 
// 如果周围的点都高于或低于当前点, 那么这个就是一个山谷或山峰
#include <iostream>
#include <queue>

using namespace std;

#define x first
#define y second
typedef pair<int, int> PII;

const int N = 1010;
int n;
int h[N][N];
int st[N][N];
PII q[N * N];

void bfs(int sx, int sy, bool& has_higher, bool& has_lower)
{
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    st[sx][sy] = true;
    while (hh <= tt)
    {
        PII t = q[hh ++ ];
        // 判断自己周围 8 个方位
        for (int i = t.x - 1; i <= t.x + 1;  ++ i )  
            for (int j = t.y - 1; j <= t.y + 1; ++ j )
            {
                if (i == t.x && j == t.y) continue;     // 自己不用判断
                if (i < 0 || i >= n || j < 0 || j >= n) continue;   // 越界
                
                if (h[i][j] != h[t.x][t.y])   // 山脉的边界
                {
                    if (h[i][j] > h[t.x][t.y]) has_higher = true;   // 判断自己周围有山峰还是山谷, 如果都有自己就什么也不是
                    else has_lower = true;    
                }
                else if (!st[i][j])         // 没判断过的格子进队列, 队列中只能有自己的同类集合, 所以只能用 else if, 
                {                           // 判断自己周围, 如果是同类且没有遍历过, 就进入队列 
                    q[ ++ tt] = {i, j};     // 用自己的同类感染到所有和自己一样的区块
                    st[i][j] = true;
                }
            }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < n; j ++ )
            scanf("%d", &h[i][j]);
    
    
    int peak = 0, valley = 0;
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < n; j ++ )
            if (!st[i][j]) // 如果该位置没有看过
            {
                bool has_higher = false, has_lower = false;
                bfs(i, j, has_higher, has_lower);
                if (!has_higher) peak ++ ;
                if (!has_lower) valley ++ ;
            }

    printf("%d %d\n", peak, valley);
    return 0;
}