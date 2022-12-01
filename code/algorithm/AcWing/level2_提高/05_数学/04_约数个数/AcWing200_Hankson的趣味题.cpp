// a, b, c, d
// x 满足: (a,x) = b, [c,x] = d
// 因为 c,x 是 d 的倍数, 所以最直观的做法是, 枚举 d 的所有约数, 对于每个约数进行判断, 是否满足所有条件, 这两个等式是否成立
// (a,x) = b 用欧几里得来判断, [c,x] = d, [c,x] = cx/(c,x)
// 
// 时间复杂度:
// 因为 2*10^9 有 1536 个约数个数, 2^31-1 有 1600 个约数个数
// 对于每个测试数据来说判断所需时间最多 1600 x logn(30) x 2000(测试数据)
// 
// 如何枚举 d 的约数: 枚举约数一般都在 √n 的复杂度, O(T*logn*√n)会有一个数据被卡 （T:测试数据)
// 所以可以枚举所有数的质数, 就会快很多
// 1) 先将 d 分解成质因式相乘的形式, 利用质数去尝除就比较快

#include <iostream>

using namespace std;

typedef long long LL;
const int N = 50010;

int primes[N], cnt; // 存储所有质数
bool st[N];         // 记录每个数是不是合数

struct Factor   // 存储 b1 的所有质因子及个数
{
    int p, s;
}factor[1601];
int fcnt;

int divider[N], dcnt;

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

void dfs(int u, int p)
{
    if (u == fcnt)  // u 已经是最后一个数了
    {
        divider[dcnt ++ ] = p; // 存下来
        return;
    }

    // 枚举当前质因子次数
    for (int i = 0; i <= factor[u].s; ++ i )
    {
        dfs(u + 1, p);
        p *= factor[u].p;
    }
}

// 筛出所有质数
void init(int n)
{
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] * i <= n; ++ j )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

// 搜索就是拼凑法, 我们已经将 d 分解出了所有质因子, 那么这些质因子相乘凑出的所有的乘积就都是 d 的约数
// 我们就是依次枚举每个约数 c, 然后枚举用几个 c 来拼乘积, 假设 d 分解出了 x 个 c
// 那么 0 个 c 相乘一直到 x 个 c 相乘它都会是 d 的约数, 我们就是将所有的约数都靠质因子之间的不同的搭配来拼凑出来
// 只要枚举完所有质因子各用多少个, 然后乘在一起, 整个就是 d 的约数之一, 我们将他及时的记录下来, 等到全部的搜索结束, 就能得到 d 的所有约数了
int main()
{
    //预处理出 1 ~ sqrt(2 * 1e9) 之间的所有质数
    init(N - 1); 
    
    int n; scanf("%d", &n);
    // 读入所有测试数据
    while (n -- )
    {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
        
        fcnt = 0;
        int t = d;  // 将 d 分解出的质因子存入 factor
        
        for (int i = 0; primes[i] <= t / primes[i]; ++ i )
        {
            int p = primes[i];  // 质数
            if (t % p == 0)
            {
                int s = 0;
                while (t % p == 0) t /= p, ++ s;    // 指数个数(质因数出现次数)
                factor[fcnt ++ ] = {p, s};  // p:质数, s:指数
            }
        }
        if (t > 1) factor[fcnt ++ ] = {t, 1};

        // 用 d1 的所有质因子平凑出d1的所有数
        dcnt = 0;
        dfs(0, 1);

        // 枚举出所有约数, 记录满足条件的数的个数
        int res = 0;
        // x 满足: (a,x) = b, [c,x] = d
        for (int i = 0; i < dcnt; ++ i )
        {
            int x = divider[i];
            if (gcd(x, a) == b && (LL)x * c / gcd(x, c) == d) res ++ ;
        } 
        printf("%d\n", res);
    }
    return 0;
}