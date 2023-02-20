// 本题只有0和1两种权重
// 扩展出来的是0的插在队头, 扩展出为1的插入在对尾
// 双度端队列广搜
// 
// 例:
// 如果是 '\', 就可以从 [1,1] 走到右下 [2,2] 和左上 [0,0] 
// 如果是 '/', 就可以从 [1,1] 走到右上 [0,2] 和左下 [2,0]
// 就可以得到:
//   [-1,-1] __ [-1,+1]
//          |\/|   
//          |/\| 
//   [+1,-1]    [+1,+1]
//
// dx[4] = {-1, -1, 1, 1}, dy[4] = {-1, 1, 1,-1}
//
// 00100
// 00111
// 10000
// 只要非负权上做, dijsktra 都是正确的
// 
// p1:只有偶点能到
// 为什么只有偶数点能到奇数点不能到 ?
//    先计算一下每个点的横纵坐标之和, 因为我们走一定是沿着斜线走的
//    如果横纵坐标是偶数, 那么走到的点的和也只能是偶数(奇点和偶点) 
//    所以不会走到奇数
//
// p2:格点的长度比格子多1
#include <iostream>
#include <cstring>
#include <deque>

using namespace std;

typedef pair<int, int> PII;

const int N = 510, M = N * N;

int n, m;
char g[N][N];
int dist[N][N];
bool st[N][N];

// 该算法, 每个点会被更新多次, 类似 dijsktra 的松弛更新
int bfs()
{
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    dist[0][0] = 0;
    deque<PII> q;
    int dx[4] = {-1, -1, 1, 1}, dy[4] = {-1, 1, 1,-1};
    int ix[4] = {-1, -1, 0, 0}, iy[4] = {-1, 0, 0, -1}; // 从定点走向格子的关系
    char cs[5] = "\\/\\/";      // 实际为: "\/\/", // 为转意字符

    q.push_back({0, 0});
    while (q.size())
    {
        auto t = q.front(); 
        q.pop_front();
        
        int x = t.first, y = t.second;
        if (st[x][y]) continue;         // 如果这个点之前更新过
        st[x][y] = true;

        // 4 个方向的扩展
        for (int i = 0; i < 4; ++ i )
        {
            int a = x + dx[i], b = y + dy[i];      // 格点上的坐标
            if (a < 0 || a > n || b < 0 || b > m) continue;     // 格点的长度比格子多一, 所以这里是严格大于n
            int ca = x + ix[i], cb = y + iy[i];        // 来到当前格子
            int d = dist[x][y] + (g[ca][cb] != cs[i]); // 从 [t.x,t.y] 出发, 四个方向的线条是否属于自己的预期
            // 松弛更新:如果 d 小于之前的距离
            if (d < dist[a][b])
            {
                dist[a][b] = d;
                if (g[ca][cb] != cs[i]) q.push_back({a, b});
                else q.push_front({a, b});
            }
        }
    }
    return dist[n][m];
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i ++ ) scanf("%s", g[i]);

        int t = bfs();

        if (t == 0x3f3f3f3f) puts("NO SOLUTION");
        else printf("%d\n", t);
    }
    return 0;
}