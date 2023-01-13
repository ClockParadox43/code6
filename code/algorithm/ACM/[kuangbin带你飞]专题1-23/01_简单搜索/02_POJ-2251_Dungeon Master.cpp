// 这道题用到了三维的数组(在原先的二维数组基础上多一个参数记录层数), 地图是类似于一层一层往上走的那种
// 由于是最短的时间的问题, 所以我们采取bfs() 进行搜索
// 
// bfs() 从 6 个方向搜 (因为是三维的, 除了平面的走法还可以向上层走), 每次记录时间miu[z][x][y], miu[z][x][y]是位于那个位置的时间, 
// 然后继续往外扩一圈(6个方向都走一次算一圈)，以此类推，直到碰触到终点，时间即为最短
// 
// 记得考虑一下边界问题
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
const int MAXN = 1e2 + 22;

struct node
{
    int _z, _x, _y;
    node(int z, int x, int y)
        :_z(z), _x(x), _y(y)
    {}
};
int level, row, col;        // 层, 行, 列
char g[MAXN][MAXN][MAXN];   // 图
bool st[MAXN][MAXN][MAXN];  // g[z,x,y] 是否访问过
int miu[MAXN][MAXN][MAXN];  // 从起点到 g[z,x,y] 的时间, 记录最短时间
int dz[6] = { 0, 0, 1, 0, 0, -1 };    // 偏移量: 北, 东, 上, 南, 西, 下
int dx[6] = { 1, 0, 0, -1, 0, 0 };
int dy[6] = { 0, 1, 0, 0, -1, 0 };

int bfs(node start, node end)
{
    queue<node> q;
    q.push(start);
    st[start._z][start._x][start._y] = 1;   // 终点标记为来过了

    while (q.size())
    {
        node p = q.front(); q.pop();
        int z = p._z, x = p._x, y = p._y;    // 弹出队列坐标, 用当前坐标更新出周围的点
        for (int i = 0; i < 6; ++i)
        {
            int ne_z = z + dz[i], ne_x = x + dx[i], ne_y = y + dy[i];

            node tp = node(ne_z, ne_x, ne_y);

            if (tp._z == end._z && tp._x == end._x && tp._y == end._y)      // 如果到达终点, 那么 z,x,y 再走一步就到达终点了
                return miu[z][x][y] + 1;

            // 判断偏移后的点是否合法
            if (tp._z < 0 || tp._z >= level || tp._x < 0 || tp._x >= row || tp._y < 0 || tp._y >= col) continue; // 边界条件
            if (st[tp._z][tp._x][tp._y] || g[tp._z][tp._x][tp._y] == '#') continue; // 图中不可以通行的条件
            
            st[tp._z][tp._x][tp._y] = true;
            miu[tp._z][tp._x][tp._y] = miu[z][x][y] + 1;
            q.push(tp);
        }
    }

    return -MAXN;
}

int main()
{
    while (scanf("%d%d%d", &level, &row, &col))
    {
        // 初始化, 不止一组测试用例
        memset(g, 0, sizeof g);
        memset(st, 0, sizeof st);
        memset(miu, 0, sizeof miu);
        node start(0, 0, 0), endin(0, 0, 0);
        if (!level && !row && !col) break;

        for (int k = 0; k < level; ++k)
            for (int i = 0; i < row; ++i)
                for (int j = 0; j < col; ++j)
                {
                    cin >> g[k][i][j];       // 第 k 层的第 i 行第 i 列, 这里有个坑, 会输入空格, 用 cin 过滤
                    if (g[k][i][j] == 'S') start = node(k, i, j);   // 起点
                    if (g[k][i][j] == 'E') endin = node(k, i, j);   // 终点
                }

        int ans = bfs(start, endin);
        if (ans == -MAXN)
            cout << "Trapped!" << endl;
        else
            cout << "Escaped in " << ans << " minute(s)." << endl;
    }
    return 0;
}
