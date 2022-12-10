#include <iostream>

using namespace std;

typedef long long LL;

const int N = 20, mod = 1e9 + 7;

LL A[N];
int down = 1;       // 求组合数的 up, down

int qmi(int a, int k, int p)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

// 求组合数
int C(LL a, LL b)
{
    if (a < b) return 0;
    int up = 1;
    for (LL i = a; i > a - b; -- i ) up = i % mod * up % mod;   // i 是 10^14, 相乘会爆 LL, 所以取个模
    return (LL)up * down % mod;     // 费马小定理
}

// N: 隔板 => yi = xi + 1, 累加 N 给 1 就是隔板 
// M: 一个合法方案花的总数
//
// xi: 第 i 个盒子花的数量 (xi <= xn)
// Ai: 第 i 给盒子中的总数 (xi <= Ai)
// 1) xi <= Ai  => 找到符合所有条件才能作为一种方案数
// 2) xi > Ai = xi >= Ai + 1 => 找到不满足其中一个条件的方案, 然后将这些方案减去
//    xi > Ai 记作 Si
// 3) 得到 C(M+N-1,N-1) - |s1∪s2∪s2...∪sn| => 用容斥原理求出即可
// 4) 求 Si: 假设求 S1, 就代表我们必须从第一组里至少取出 A1 + 1 朵花(保证不合法)
//           此时还剩 M - (A1 + 1) 朵花, 剩下的就是隔板
//           那么此时的方案数就是 C(M+N-1-(A1+1), N-1)
//    |s1∩s2|同理: C(M+N-1-(A1+1)-(A2+1), N-1)
int main()
{
    LL n, m; scanf("%lld%lld", &n, &m);
    
    for (int i = 0; i < n;  ++ i ) scanf("%lld", &A[i]);    // 输入

    // 因为所有 b 的运算都是一样, 所以 down 的运算可以提到 C 函数的外面去
    for (int j = 1; j <= n - 1; ++ j ) down = (LL)j * down % mod;
    down = qmi(down, mod - 2, mod); // 分子1/(n-1)! 通过快速幂逆元 

    int res = 0;
    // 整体思路: 实现从 0 枚举到 2^n-1, 把每个条件数当成一个二进制数, 第 i 位为 1 代表符合条件, 正负号取决于条件个数(二进制中 1 的个数)奇偶性
    //          条件为奇数, 符号为 '-', 条件为偶数, 符号为 '+'

    // 容斥原理 => 从 0 枚举到 2^n (容斥原理选和不选项的数量一共是 2^n)
    for (int i = 0; i < 1 << n; ++ i )
    {
        LL a = m + n - 1, b = n - 1;   // 总方案数: C(m+n-1, n-1) 
        
        int sign = 1;       // 符号标记是正数还是负数

        for (int j = 0; j < n; ++ j )   // 将 1 看做一个二进制数, 看下 n 位数字有多少个 1 
            if (i >> j & 1)             // 如果当前第 j 位数字是 1, 符合变换后的条件就减去
            {
                sign *= -1;    // 改变正负号
                a -= A[j] + 1; // "分母" 减去条件 j 数 A[j]+1 - A[j]-1 => 转换后严格大于 Ai, 就是 >= Ai+1 
            }

        res = (res + C(a, b) * sign) % mod; // 偶数就加
    }

    cout << (res + mod) % mod << endl;      // 余数要求正数所以先加上一个 mod 再模掉

    return 0;
}