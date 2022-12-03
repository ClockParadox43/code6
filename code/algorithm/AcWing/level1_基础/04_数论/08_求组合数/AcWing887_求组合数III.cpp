// 20 组询问, 1≤b≤a≤10¹⁸ => 卢卡斯定理
// C(a,b) ≡ C(a mod p, b mod p) · C(a/p, b/p) (mod p) 
//      ps: 两个式子在 mod p 的情况下同余
//
// 时间复杂度: logₚN·p·logp     ps: 因为是把 a, b 变成 p 进制所以是 log 以 p 为底的 N
//        
// 证明:
// 会用到两个等式(展开左边的每一项即可得证明): 
//      (1 + x)ᵖ ≡ (1 + xᵖ) (mod p)
//      (1 + x)ᵖ^ᵃ ≡ (1 + xᵖ^ᵃ) (mod p)
// 
// 1) 把 a, b 转化成 p 进制
//      a = aₖ·pᵏ + aₖ₋₁·pᵏ⁻¹ + ... + a₀·p⁰
//      b = bₖ·pᵏ + bₖ₋₁·pᵏ⁻¹ + ... + b₀·p⁰
// 
// 2) 拿出一项, 将上面展开的 a 代入
//    则有:  (1 + x)ᵃ
//         = (1 + x)ᵃᵏ˙ᵖ^ᵏ ⁺ ᵃᵏ⁻¹˙ᵖ^ᵏ⁻¹ ⁺...⁺ ᵃ¹˙ᵖ^¹ ⁺ ᵃ⁰˙ᵖ^⁰
//         = (1 + x)ᵃᵏ˙ᵖ^ᵏ · (1 + x)ᵃᵏ⁻¹˙ᵖ^ᵏ⁻¹ ·...· (1 + x)ᵃ¹˙ᵖ^¹ · (1 + x)ᵃ⁰˙ᵖ^⁰
//         = (1 + xᵖ^ᵏ)ᵃᵏ · (1 + xᵖ^ᵏ⁻¹)ᵃᵏ⁻¹ ·...· (1 + xᵖ^¹)ᵃ¹ · (1 + xᵖ^⁰)ᵃ⁰ (mod p)
//
// 3) 等式左边展开出来 x^b 的系数是 Cab, 右边也要求 X^b 的系数, 这样可以列个等式 
//    由 b 的 p 进制可得: xᵇ = xᵇᵏ˙ᵖ^ᵏ ⁺ ᵇᵏ⁻¹˙ᵖ^ᵏ⁻¹ ⁺...⁺ ᵇ¹˙ᵖ^¹ ⁺ ᵇ⁰˙ᵖ^⁰
//    显然, xᵇᵏ˙ᵖ^ᵏ 项在 (1 + xᵖ^ᵏ)ᵃᵏ 中是 C(ak, bk) · xᵇᵏ˙ᵖ^ᵏ.
//    同理, 后面的以此类推, 同理可求 xᵇ 的系数为 C(ak,bk) · C(ak-1,bk-1) ·...· C(a1,b1) · C(a0,b0)
// 
//    因此可得: Cab ≡ C(ak, bk) · C(ak-1, bk-1) · ... · C(b1,a1) · C(a0,b0) (mod p)
// 
// 已经得到了答案, 只需要转化成简单形式:
// 因为 a, b 是 p 进制数, 所以有 a0 = a mod p, b0 = b mod p
// 我们让 a, b 在 p 进制中右移一位, 即 ⌊a/p⌋, ⌊b/p⌋
// 对于 a/p⌋, ⌊b/p⌋ 重复上面最开始的步骤, 可以得到 C(⌊a/p⌋, ⌊b/p⌋) ≡ C(ak,bk) · C(ak-1, bk-1)·…·C(a1,b1) (modp)
// 因此: C(a,b) ≡  C(⌊a/p⌋, ⌊b/p⌋) · C(a mod p, b mod p) (mod p) 
// 公式推导: https://zhuanlan.zhihu.com/p/452976974 

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

int qmi(int a,int k,int p)
{
    int res = 1;
    while(k)
    {
        if(k & 1)res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

// C 从定义出发
int C(int a,int b,int p)// 自变量类型int
{
    if(b > a)return 0;// 漏了边界条件
    int res = 1;
    // a!/(b!(a-b)!) = (a-b+1)*...*a / b! 分子有b项
    for(int i = 1, j = a;i <= b; i ++, j -- )//i<=b而不是<
    {
        res = (LL)res * j % p;
        res = (LL)res * qmi(i, p-2, p)%p;
    }
    return res;
}

//对公式敲
int lucas(LL a, LL b, int p)
{
    if(a < p && b < p)return C(a, b ,p);    // lucas递归终点是C_{bk}^{ak}
    return (LL)C(a % p, b % p, p) * lucas(a / p, b / p, p) % p;   // a%p后肯定是小于 p 的, 所以可以用 C(), 但 a/p 后不一定 <p 所以用 lucas 继续递归
}

int main()
{
    int n;
    cin >> n;
    while(n -- )
    {
        LL a, b;
        int p;
        cin >> a >> b >> p;
        cout << lucas(a, b, p) << endl;
    }
    return 0;
}