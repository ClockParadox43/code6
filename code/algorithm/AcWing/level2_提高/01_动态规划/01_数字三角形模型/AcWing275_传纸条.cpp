// 状态表示:
//      集合: 所有第一条路线(1,1)走到(x1,k-x1), 第二条路线(1,1)走到(x2,k-x2)到路线组合的集合
//      属性: Max
//
// 第一步是前面 k-1 步的路线(把前面做过的决定扣出来), 第二步是最后一步的路线(拼给当前方案)


#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 55;

int n, m;
int g[N][N];
int f[N * 2][N][N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            scanf("%d", &g[i][j]);

    for (int k = 2; k <= n + m; k ++ )
        for (int i = max(1, k - m); i <= min(k-1, n); i ++ )      // k 一开始很小, 可能会得到负数 所以取 max
            for (int j = max(1, k - m); j <= min(k-1, n); j ++ )  // k=x1+y1=x2+y2, k 是横纵坐标之和, 所以 i<k,j<k 
            {               
                int t = g[i][k - i]; // k-i:纵坐标
                if (i != j) t += g[j][k - j];
                for (int a = 0; a <= 1; a ++ )  // 枚举偏移量
                    for (int b = 0; b <= 1; b ++ )              
                        f[k][i][j] = max(f[k][i][j], f[k - 1][i - a][j - b] + t);
            }
    printf("%d\n", f[n + m][n][n]);

    return 0;
}




