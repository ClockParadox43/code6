// Sum(A)=(1+p11+p21+...+pα11)∗(1+p12+p22+...+pα22)∗...∗(1+p1n+p2n+...+pαnn)
// 解释:每个括号里面就是每一个质数的任一个次幂(次幂范围 [0,αi])之和, 如果把括号拆开 
//      就是每个括号里面选一个数乘起来，再把所有选择加起来. 每个括号选一个数乘起来 
//      不正对应每一个约数的值吗? 所以约数和就是上面这个式子, 所有约数相加就是约数之和
// 
//          n    ai  j
// Sum(A) = ∏  ( ∑  p )
//         i=1  j=0  i
#include <iostream>
#include <unordered_map>

using namespace std;

const int mod = 1e9 + 7;
typedef long long LL;

int main()
{
    int _;
    scanf("%d", &_);
    
    unordered_map<LL, int> primes;
    while (_ -- )
    {
        int n;
        cin >> n;
        // 分解质因数, 将和最小质因子有关的合数都筛掉
        for (int i = 2; i <= n / i; ++ i )
            while (n % i == 0) n /= i, primes[i] ++ ;
        if (n > 1) primes[n] ++ ;
    }
    
    int res = 1;
    // 每个质因数相加
    // 12 = 2^2 + 3^1
    // t = t * a + 1 
    // t = 1 * 2 + 1 = 3
    // t = 3 * 2 + 1 = 7
    //      = = =
    // t = 3 * 3 + 1 = 4
    // 7 * 4 = 28 
    for (auto p : primes)
    {
        // a:质因数, b:指数
        int a = p.first, b = p.second;
        LL t = 1;
        // t = t * a + 1 从结果出发, 有个p的零次方要表示(循环只能 2 次)
        // 哈希处理, 其实就是提取因子, 类似于初中学的那个秦九韶算法
        while (b -- ) t = (t * a + 1) % mod;
        res = res * t % mod;
    }
    
    cout << res << endl;
    
    return 0;
}