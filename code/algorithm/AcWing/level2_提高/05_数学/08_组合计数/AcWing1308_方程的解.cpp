// a₁ + a₂ +...+ aₖ = n, 要求 aᵢ = {i = 1,2,..,k} 
// 共有多少种 {a₁ + a₂ +...+ aₖ} 的组合能够满足上述方案
//
// 组合数 IV 原来还可以用组合数 I 的公式, 结合高精度加法来做
//
// 隔板法:
//    构造 n 个小球 * * * * * * *, 则 n 个小球共有 n-1 个空隙
//    每插入一个空隙, 从该空隙向左直到遇到第一个板子或左边界为止这个区间的和, 记作该数 aᵢ 的值
//    则一共插入 k-1 个板子, 就可以把原区间分成 k 个子区间, 每个子区间的和也就刚好对应了原来的 k 个数
//    例如: n = 7, k = 4 时 * *|* *|* *|* 是一种方案, 对应了, {a₁ = 2, a₂ = 2, a₃ = 2, a₄ = 1}
// 则总方案数为: C(n-1,k-1) => 在 n-1 个空隙中选出 k-1 个板子
//
// 本题思路:
//      1) 快速幂求 n = xˣ
//      2) 隔板法求出组合数 C(n-1,k-1) 
//
// 本题答案没有要求取模, 答案上界的极限是 C(100,1000) ≈ 10^143 必爆 int 和 longlong
// 需要手写高精度(具体参考基础课求组合数的方法: 高精度 + 递推)
#include <iostream>

using namespace std;

const int N = 150, mod = 1000;

int k, x;            // a₁ + a₂ +...+ aₖ = g(x), 其中 x ≥ 1 且 k∈ N*, x 是正整数
int f[1000][100][N]; // 前两位是组合数, 后一位是高精度

int qmin(int a, int b)
{
    int res = 1;
    for (int i = b; i; i >>= 1)
    {
        if (i & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

// 加法高精度 a = b + c 
void add(int a[N], int b[N], int c[N])
{
    for (int i = 0, t = 0; i < N; ++ i )
    {
        t += b[i] + c[i];
        a[i] = t % 10;
        t /= 10;
    }
}

int main()
{
    scanf("%d%d", &k, &x);

    // n = x^x
    int n = qmin(x % mod, x);
    
    // 求组合数 C(n-1, k-1)
    // 递推式: C(i,j) = C(i-1,j-1) + C(i-1,j)
    for (int i = 0; i < n; ++ i )
        for (int j = 0; j <= i && j < k; ++ j )
        {
            if (!j) f[i][j][0] = 1;
            else add(f[i][j], f[i - 1][j], f[i - 1][j - 1]);  // 求组合数 1 
        }
    
    // 输出答案 C(n-1,k-1)
    int it = N - 1;
    while (!f[n - 1][k - 1][it]) -- it; // 0 就一直回退
    while (it >= 0) cout << f[n - 1][k - 1][it -- ];   // 高精度: 高精度在第三层, 直接输出即可
    return 0;
}