// 矩阵中的任意一个区域出发, 当前高度必须大于下一个将要去的高度
// 状态表示:所有从 (i,j) 开始滑的路径
// 集合划分:上,下,左,右 (右:f[i,j] -> f[i,j+1])
//          所有集合减去同一个值不会影响最后结果, 所以就变成求从 f[i,j+1] 这个点滑的最大长度
//          因为这是除了第一步的最大长度所以还要再加个 1, f[i,j+1]+1
//          初始化时设置 1 加上和 f[i,j+1]+1 是等价的
// 状态计算: 
//
// 证明一定不会存在环, a -> b -> c -> d
//                     |______________↑
//                    a > b > c > d
//                    如果 d > a, 那就存在矛盾
// 
// 这题本质是个DAG最长路问题, 借递归实现逆拓扑序递推

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 310;

int n, m;
int g[N][N];
int f[N][N];        // 从 [i,j] 开始滑的路径求最长

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int dp(int x, int y)
{
    int& v = f[x][y];
    if (v != -1) return v;      // 记忆化搜索

    v = 1;
    for (int i = 0; i < 4; ++ i )   // 每来到一个点枚举上下左右 4 个方向
    {
        int a = x + dx[i], b = y + dy[i];       // 当前坐标加上偏移量
        if (a >= 1 && a <= n && b >= 1 && b <= m && g[x][y] > g[a][b])
            v = max(v, dp(a, b) + 1);
    }

    // 每次返回的都是当前点枚举上下左右枚举出的最好路径
    return v;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i )
        for (int j = 1; j <= m; ++ j )
            scanf("%d", &g[i][j]);
    
    memset(f, -1, sizeof f);
    // 枚举每个坐标
    int res = 0;
    for (int i = 1; i <= n; ++ i )
        for (int j = 1; j <= m; ++ j )
            res = max(res, dp(i, j));

    printf("%d", res);

    return 0;
}