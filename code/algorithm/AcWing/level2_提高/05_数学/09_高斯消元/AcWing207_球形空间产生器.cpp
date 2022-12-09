// 1) 根据题意得到线性方程组:
//      (a₁₁ - x₁)² + (a₁₂ - x₂)² + ... + (a₁ₙ - xₙ)² = R² (1)
//      (a₂₁ - x₁)² + (a₂₂ - x₂)² + ... + (a₂ₙ - xₙ)² = R² (2)
//      ... ...
//      (aₙ₊₁₁ - x₁)² + (aₙ₊₁₂ - x₂)² + ... + (aₙ₊₁ₙ - xₙ)² = R²(n+1)
//
// 2) 进行公式转换
//    例: 其中一项 (2) - (1)
//    (a₁₁ - x₁)² = a₁₁² + x₁² - 2a₁₁x₁
//    (a₂₁ - x₁)² = a₂₁² + x₁² - 2a₂₁x₁
//    因式分解后, 移项
//    = a₁₁² + x₁² - 2a₁₁x₁ - a₂₁² + x₁² - 2a₂₁x₁
//    = a₂₁² - a₁₁² - 2(a₂₁ - a₁₁)x₁
//    a₂₁² - a₁₁² = 2(a₂₁ - a₁₁)x₁ ...
#include <iostream>
#include <cmath>

using namespace std;

const int N = 15;

int n;
double a[N][N], b[N][N];    // a[][]:系数矩阵, b[][]:整理完后的结果

void Gauss()
{
    // 化成上三角形
    for (int r = 1, c = 1; r <= n; ++ r, ++ c)
    {
        // 找到主元
        int t = r;
        for (int i = r + 1; i <= n; ++ i )
            if (fabs(b[i][c]) > fabs(b[t][c]))
                t = i;

        // 交换第 r 行和第 t 行的元素
        for (int i = c; i <= n + 1; ++ i ) swap(b[r][i], b[t][i]);
        // 主元归一(第 r 行除以主元系数)
        for (int i = n + 1; i >= c; -- i ) b[r][i] /= b[r][c];
        // 消元 (用该行把下面所有行的第 c 列消为 0)
        for (int i = r + 1; i <= n; ++ i )
            for (int j = n + 1; j >= c; -- j )
                b[i][j] -= b[r][j] * b[i][c]; 
    }

    // 化成行最简阶梯型 (本题唯一解, 故同样也是对角矩阵)
    for (int i = n; i > 1; -- i )
        for (int j = i - 1; j >= 1; -- j )
        {
            b[j][n + 1] -= b[i][n + 1] * b[j][i];
            b[j][i] = 0; 
        }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i <= n; ++ i )
        for (int j = 1; j <= n; ++ j )
            scanf("%lf", &a[i][j]);
    
    // 转化为线性方程
    // a₂₁² - a₁₁² = 2(a₂₁ - a₁₁)x₁
    // 因为公式是下标从 0 开始, 所以 1~n 就是第 2 个到第 n+1 个公式 
    for (int i = 1; i <= n; ++ i )
        for (int j = 1; j <= n; ++ j )
        {
            b[i][j] =  2 * (a[i][j] - a[0][j]);
            b[i][n + 1] += a[i][j] * a[i][j] - a[0][j] * a[0][j];
        }

    // Gauss 消元
    Gauss();
    // 输出答案
    for (int i = 1; i <= n; ++ i )
        printf("%.3lf ", b[i][n + 1]);
    
    return 0;
}