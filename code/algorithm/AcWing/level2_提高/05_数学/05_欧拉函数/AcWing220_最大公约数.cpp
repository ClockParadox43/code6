// 给定整数 N, 求 1≤x, y≤N 且 gdc(x,y) 为素数的数对, (x,y) 有多少对
//
// 解: (x,y) = p, 枚举 [1,N] 种所有的 p, 
// (x,y) = p 也就意味着 (x/p,y/p) = 1
// 每个数除以他的最大公因数一定数值, 这是显然的
// 
// (x/p,y/p) = 1, 记作 (x',y') = 1
// 1 ≤ x', y' ≤ N/p,  
// 也就是统计有多少 (x',y') 在 [1,N/p] 范围内, 满足 (x',y') = 1
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e7 + 10;

int primes[N], cnt;
bool st[N];
int phi[N];
LL s[N];

// 欧拉函数 
void init(int n)
{
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i])
        {
            primes[cnt ++ ] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] * i <= n; ++ j )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) 
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
    // 前缀和
    // 因为题目是给定一个 n 快速得到其中的值
    // 1~n 内每个数对应的欧拉函数对数的和
    // 1 到 n/p的质数对 = s[n/p] * 2 + 1;
    for (int i = 1; i <= n; ++ i ) s[i] = s[i - 1] + phi[i];
}

int main()
{
    int n; scanf("%d", &n);
    init(n);

    LL res = 0;
    for (int i = 0; i < cnt; ++ i )
    {
        int p = primes[i];          
        res += s[n / p] * 2 + 1; // 求 [1,n/p] 欧拉函数的和
    }

    printf("%lld\n", res);
    return 0;
}