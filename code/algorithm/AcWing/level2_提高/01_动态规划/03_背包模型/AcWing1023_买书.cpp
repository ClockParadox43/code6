// 状态表示f[i,j]: 一共有 n 个物品, 每个物品有体积 vi, 价值 wi, 每个物品能够选多次
//                 求总体积不超过 m 的方案数
//           属性: cnt
// 转态转移:   选择第i本书:f[i-1,j-kv]
//           不选择第i本书:f[i-1,j]
//           f[i,j] 就是总方案数
#include <iostream>

#define N 1005
using namespace std;

int m;
int f[N][N];
int v[5] = {0, 10, 20, 50, 100};

int main()
{
    cin >> m;
    f[0][0] = 1;
    for (int i = 1; i <= 4; ++ i)
        for (int j = 0; j <= m; ++ j)   
            for (int k = 0; k * v[i] <= j; ++ k)
                f[i][j] += f[i - 1][j - k * v[i]];
                
    cout << f[4][m];
    return 0;
}