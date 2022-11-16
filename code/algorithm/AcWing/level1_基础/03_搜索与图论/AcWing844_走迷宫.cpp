// 求最短路问题包含了 DP 问题
// 当所有边的权重都一样的时候, 才可以用 BFS 求最短路, 一般都用最短路算法求最短路
// 深搜得到的顺序可能是随机的, 因此不适合求最短路径
//
// 宽搜是一层一层往下搜索, 所以搜到的第一个, 一定是最短路
//
// 宽搜基本框架: 
//  1) 初始状态放入 queue
//  2) while 保证队列不空
//      - 每次拿出队头
//        扩展队头
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

const int N = 110;

int n, m;
int g[N][N];
int d[N][N];    // 到 [x,y] 的距离
PII q[N * N];   // 队列

// 想算到当前 [x,y] 的距离, 就把之前的距离加上方向的偏移量, 就是当前位置的坐标
int bfs()
{
    int hh = 0, tt = 0;
    q[0] = {0, 0};
    
    memset(d, -1, sizeof d);
    d[0][0] = 0;            // 该题是从 0 开始
    // 向量
    // x:行, y:列
    // u, r, d, l
    int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };

    while (hh <= tt)
    {
        auto t = q[hh ++ ];
        // 枚举四个方向
        for (int i = 0; i < 4; ++ i )
        {
            // 当前方向
            int x = t.first + dx[i], y = t.second + dy[i];
            // (x,y) 不越界
            // 并且该点没有走过 只有图是权值是 0 的时候才可以走
            if (x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 0 && d[x][y] == -1)
            {
                d[x][y] = d[t.first][t.second] + 1;   // 当前距离 = 前一个距离 + 1
                q[ ++ tt] = {x, y};                 // 当前可以走的坐标入队列
            }
        }
    }

    return d[n - 1][m - 1];
}

int main()
{
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> g[i][j];

    cout << bfs() << endl;
}

