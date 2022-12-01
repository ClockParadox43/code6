#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1000010;

int primes[N], cnt;
int phi[N];
bool st[N];

// 1~N 中与 N 互质的数的个数被称为欧拉函数, 记为ϕ(N)
// 若在算数基本定理中, N=p1^α1, p2^α2 ... pk^αk, 则：
// ϕ(N) = N ∗ (p1−1/p1) ∗ (p2−1/p2) ∗ ... *( pk−1/pk)
//
// 质数 i 的欧拉函数即为 phi[i] = i - 1 -> 1 ~ i−1 均与 i 互质, 共i−1个
// phi[primes[j] * i] 分为两种情况: 
// 1) i % primes[j] == 0时: p[j] 是 i 的最小质因子, 也是 p[j] * i 的最小质因子, 因此 1 - 1 / p[j] 这一项在 phi[i] 中计算过了 
//    只需将基数 N 修正为 p[j] 倍, 最终结果为 phi[i] * p[j]
// 2) i % primes[j] != 0: p[j] 不是 i 的质因子, 只是p[j] * i的最小质因子, 因此不仅需要将基数 N 修正为 p[j] 倍 
//    还需要补上 1 - 1 / p[j] 这一项, 因此最终结果 phi[i] * (p[j] - 1)
// ϕ(i) = (1 - 1/pj)
// 和 pj 相比, pj 多了一个 1/pj
// ϕ(i) 比 ϕ[p[j] * i] 多出一个 p[j]
void get_eulers(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i])
        {
            primes[cnt ++ ] = i;
            phi[i] = i - 1;
        }
        
        for (int j = 0; primes[j] <= n / i; ++ j )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) 
            {
                phi[primes[j] * i] = phi[i] * primes[j];  // phi[p[j]*i] 的最小质因子, 在之前的基础上相乘
                break;
            }
            phi[primes[j] * i] = phi[i] * (primes[j] - 1);
        }
    }
}

// 求每个数的欧拉函数
int main()
{
    int n;
    scanf("%d", &n);
    
    get_eulers(n);
    LL res = 0;
    for (int i = 1; i <= n; ++ i ) res += phi[i];
    printf("%lld", res);
    
    return 0;
}