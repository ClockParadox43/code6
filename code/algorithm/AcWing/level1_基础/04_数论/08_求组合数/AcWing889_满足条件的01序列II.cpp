#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010, mod = 1e9 + 7;

// 如果 p 是质数可以用快速幂, 如果不是质数, 只能用费马小定理 
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

// ans = C(2n,n) -> C(2n,n-1) = C(2n,n)/n+1     
//         ps: C(2n,n): 一共有 2n 步, 可以挑 n 步往上走
//             C(2n,n-1): 一共有 2n 步, 有 n-1 步经的过方案数
// 
// 结论:任何条从 0 点出发经过边界的路径都可以轴对称
//     每一条从 (0,0) 走到 (6,6) 都可以对应一条从 (0,0) 走到 (5,7) 的路径
//     所以不合法的方案数就是 从 (0,0) 走到 (5,7) 的路径的不合法的方案数
//
// C(2n, n) - C(2n, n-1) 
// = 2n!/(n!*n!) - 2n!/(n-1!*n+1!)
// 最终得到: C(2n, n)/n + 1
// 
// 答案: 从 (0,0) 走到 (n,n) 不经过指定边的个数
//       求有多少条路径经过指定边
//       总方案数 - 经过的方案数就是 = 不经过的方案数
int main()
{
    int n;
    cin >> n;

    // a: 
    int a = n * 2, b = n;
    int res = 1;
    // C(2n, n) = 2n!/(n!*n!) => 2n!/(n!*n!)^-1
    for (int i = a; i > a - b; i -- ) res = (LL)res * i % mod;  // 分数倒着乘一遍再正着乘一遍
    for (int i = 1; i <= b; i ++ ) res = (LL)res * qmi(i, mod - 2, mod) % mod;  // 乘 i 的逆元

    res = (LL)res * qmi(n + 1, mod - 2, mod) % mod; // 乘 n+1 的逆元

    cout << res << endl;

    return 0;
}