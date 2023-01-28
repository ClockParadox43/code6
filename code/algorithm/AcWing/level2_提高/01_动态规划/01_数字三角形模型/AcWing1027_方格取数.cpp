// 走两次:
// f[i,j,h,k] 表示从 (1,1)(1,1) 分别走到 (i,j)(h,k) 的路径最大值
// 如何处理同一个格子(同一个格子的值只能拿一次)
// 题目说从 A 点到 B 点共走了两次, 所以我们可以设两条路径是同时出发的
// 所以两条路径时很容易想到维护当前两条路径的状态(坐标)也就是 f[x1,y1,x2,y2]
// 由于我们同时出发的条件, 我们注意到 k = x1+y1 = x2+y2 (k 是横纵坐标之和)
// 所以我们可以只用三个维度 f[k][x1][y1] 来维护就行了, 因为 y1=k-x1, y2=k-x2
// 最后按照数字三角形模型将两条路径的转移合并在一起(一共四种) 即可解决

#include <iostream>

using namespace std;
const int MAXN = 15, MAXM = MAXN << 1;

int n, x, y, c;
int w[MAXN][MAXN];
int f[MAXM][MAXN][MAXN];

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(false), cout.tie(false);
    
    cin >> n;
    while (cin >> x >> y >> c, x || y || c) w[x][y] = c;
    
    for (int k = 2; k <= n << 1; ++ k)  // k 是横纵坐标之和(k-1:找上个矩阵中到答案)
        for (int i = 1; i <= n; ++ i)   // 因为当 k 很小到时候, k-i/k-j 一定是负数所以可以优化
            for (int j = 1; j <= n; ++ j)
            {
                int _i = k - i, _j = k - j; // 纵坐标
                
                if (_i >= 1 && _i <= n && _j >= 1 && _j <= n)   // 判断纵坐标是否合法
                {
                    int t = w[i][_i];                 // 将要来到到格子, 然后枚举来自各个方位到可能性
                    if (i != j) t += w[j][_j];        // 如果两个坐标没有重合, 加上另一条路径到和
                    int &v = f[k][i][j];
                    v = max(v, f[k - 1][i - 1][j - 1] + t);
                    v = max(v, f[k - 1][i - 1][j] + t);
                    v = max(v, f[k - 1][i][j - 1] + t);
                    v = max(v, f[k - 1][i][j] + t);
                }
            }
            
    cout << f[n << 1][n][n];
    return 0;
}