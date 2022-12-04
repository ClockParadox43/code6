// 本题是一道中国剩余定理的裸题, 直接用输入数据套公式即可
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 15;

int n;
int a[N], m[N];

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a; 
    }

    LL x1, y1;
    LL res = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1; 
    return res;
}


int main()
{
    scanf("%d", &n);
    LL M = 1;
    for (int i = 0; i < n; ++ i )
    {
        scanf("%d%d", &m[i], &a[i]);
        M *= m[i];      // 读入 mi 的时候同时计算 M
    }

    LL res = 0;
    for (int i = 0; i < n; ++ i )
    {
        LL Mi = M / m[i];       // 计算 Mᵢ = M/mᵢ (每个 Mᵢ 都和 mᵢ 互质, 所以用 M 除去 mᵢ), 因为是除法所以需要求逆元
        LL ti, y;               // tᵢ 是 Mᵢ 关于 mᵢ 的逆元, 即 Mᵢtᵢ ≡ 1(mod mᵢ)
        // 这一步时求逆元, 根据逆元公式衍生的公式可以得到 tᵢ * Mᵢ + y * mᵢ = 1
        // ax + by = d
        exgcd(Mi, m[i], ti, y);
        res += a[i] * Mi * ti;      // 计算的同时累加到 res 中 (上述公式里有个 sum 需要累加) 
    }
    cout << (res % M + M) % M << endl;  // 对于任意 x+kM 都是满足要求的解, 但目标是输出最小的正整数x, 因此取模即可
    return 0;
}