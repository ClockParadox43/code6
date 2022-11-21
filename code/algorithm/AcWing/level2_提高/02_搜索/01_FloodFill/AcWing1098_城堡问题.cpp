// 我们用1表示西墙, 2表示北墙, 4表示东墙, 8表示南墙, P 为该方块包含墙的数字之和, 最大为 15
// 考虑要点, 如何处理这 4 个方向的二进制编码
// 解：  
//      _1__
//    0|___|2   看某一个方向有没有墙就是看看数字的某个方向是否有二进制 1 来表示
//       3
//    0000, 1111
// 四面墙总共有 2^4 个状态对应 0~15
#include <iostream>

using namespace std;

#define x first
#define y second
const int N = 60;
typedef pair<int, int> PII;

int n, m; 
int g[N][N];
bool st[N][N];
PII q[N * N];

int bfs(int sx, int sy)
{
    //           西 北 东 南
    // 因为是按照西北东南走, 左西 -1, 上北 -1, 右东 +1, 下南 +1
    // x,y 的表达放式是, 上 -1, 右 +1, 下 +1, 左 -1
    // 向量的表达, 按照自己喜好表达即可, 但是该题的位运算只能从低到高位枚举, 只能表示成西南东北
    int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
    int hh = 0, tt = 0;
    int area = 0;
    
    q[0] = {sx, sy};
    st[sx][sy] = true;

    while (hh <= tt)
    {
        PII t = q[hh ++ ];
        area ++ ;
        for (int i = 0; i < 4; ++ i )
        {
            int a = t.x + dx[i], b = t.y + dy[i];       // 根据偏移量在原来的坐标上进行偏移
            if (a < 0 || a >= n || b < 0 || b >= m) continue;   // 处理越界, 其实不用判边界, 边界有墙
            if (st[a][b]) continue;     // 遍历过的格子不用遍历影响时间复杂度
            if (g[t.x][t.y] >> i & 1) continue;     // 被统计的不能是墙
            q[ ++ tt] = {a, b};
            st[a][b] = true;
        } 
    }
    return area;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i )
        for (int j = 0; j < m; ++ j )   
            cin >> g[i][j];

    int cnt = 0, area = 0;      // 联通块个数, 最大面积
    for (int i = 0; i < n; ++ i )   
        for (int j = 0; j < m; ++ j )   
            if (!st[i][j])        
            {    // 遍历没有遍历过的格子
                area = max(area, bfs(i, j)), cnt ++ ;
            }
    cout << cnt << endl;
    cout << area << endl;
    return 0;
}