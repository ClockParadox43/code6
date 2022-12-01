// 欧拉函数可以求出 n 的范围内 gcd(x,y) = 1 数的个数
//
// 把每一个光线看做直线, 所有点都会在 y = kx 的直线上, k 就是斜率
// 如果一个点能被照到, 那么 x₀, y₀ 就是在直线上的第一个点 ((x₀, y₀)左下方没有一个同样在直线上的点)能被照到
// y = kx, k = y₀/x₀, 
// 将 k 代入: y = y₀/x₀·x  => 等价于 x₀ 和 y₀ 互质
// 证明:
// 假设 x₀ 和 y₀ 不互质, (x₀, y₀) = d > 0
// (x₀/d, y₀/d) 则此时有公约数必然在左下方且将 (x₀, y₀) 挡住
// 这也说明了所有被照到的点一定满足 x₀, y₀ 互质
// 
// 如果 x₀, y₀ 互质是不是不会有任何一个点在 x₀, y₀ 前面且在这个直线上
// 假设存在 x₀', y₀' 在直线上使得 y₀'/ x₀' = y₀/x₀
// ∵ y₀'/ x₀' = y₀/x₀ ∴ y₀/y₀' = x₀/x₀'
// 因为是在 x₀, y₀ 前面, 所以 x₀' < x₀, y₀' < y₀
// 这显然是矛盾的, 因为互质的话是最简分数, 所以不能被约的更小, 所以不会存在这样的 x₀, y₀ 
// 因此:
// => 被照到的 x 和 y 都是互质的
// => 问题转化为在 [0,N] 找所有互质对 (x,y) 的数量
//
// 以 y = x 为分界线, 利用左上和右下对称分布, 左上互质对数量 == 右下互质对数量
// => 只用看右下互质对数量

#include <iostream>

using namespace std;

const int N = 1010;

int primes[N], cnt;
bool st[N];
int phi[N];

// 线性筛求欧拉函数
void init(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i]) 
        {
            primes[cnt ++ ] = i;
            phi[i] = i - 1;
        }

        for (int j = 0; primes[j] * i <= n; ++ j )
        {
            st[i * primes[j]] = true;
            // 情况1: primes[j] 是 i 的最小质因子, 也是 p[j] * i 的最小质因子 
            if (i % primes[j] == 0)
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            // 情况2: priems[j] 只是 i 的最小质因子
            phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}

int main()
{
    // q: 表示 q 组测试数据
    // n: 表示 n 行 n 列
    // 求 平面直角坐标系的可见点
    init(N - 1);
    int n, q; scanf("%d", &q);
    for (int T = 1; T <= q; ++ T )
    {
        scanf("%d", &n);
        int res = 1;
        for (int i = 1; i <= n; ++ i ) res += phi[i] * 2;
        printf("%d %d %d\n", T, n, res);
    }
    return 0;
}