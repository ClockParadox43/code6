// 和 a^b 相同思路
// 类似反复平方, a*(2^i) = (a*2^(i-1))*2
// 通过 k 次递推求出每个乘积项, 当 Ci = 1 时, 将该乘积项累加到答案中即可
#include <iostream>

using namespace std;

typedef long long LL;

void test1()
{
    LL a, b, p;
    
    cin >> a >> b >> p;
    
    LL ans = 0;
    for (; b; b >>= 1 )
    {
        if (b & 1) ans = (ans + a) % p;
        // a = (a + a) % p;
        a = a * 2 % p;
    }
    cout << ans << endl;
}

// 思路2: 利用 a * b % p = a * b - a * b / p * p
// 因为 (a,b) < p, 所以 (a*b/p) 下取整后也一定 < p
// (a,b 都小于 p, 那么 a*b 划分每份要 p 个, 最后的份数一定小于 p)
// 所以我们可以用浮点数执行运算而不用关心小数点之后的那部分, long double 在十进制下的有效数字有 18~19 位, 足够胜任
// 当浮点数的精度不足以保存精确数值时, 会像科学计数法一样舍弃低位
void test2()
{
    // cout << 3 * 4 % 5 << endl;               // 2
    // cout << 3 * 4 - 3 * 4 / 5 * 5 << endl;   // 2
    LL a, b, p;
    cin >> a >> b >> p;

    a %= p, b %= p;
    
    LL c = (long double) a * b / p;
    LL ans = a * b - c * p;
    
    if (ans < 0) ans += p;
    else if (ans >= p) ans -= p;
    
    cout << ans << endl; 
}

int main()
{
    // test1();
    test2();
    return 0;
}