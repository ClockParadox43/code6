// d|a, d|b, d|a+b
// d|a, d|b, d|ax+by
// (a,b) = (b, a mod b)         
// a mod b = a - (a / b) * b  -> 乘法逆运算
//    记作 : a - c * b
// 例: 
//  24%16 = 24-(16|24)*16
//      8 = 24-1*16
//   24%8 = 24-(8|24)*8
//      0 = 24-24
//
// (a,b) = (b, a mod b)
// (a,b) = (b, a-c*b)
// 
// d|a, d|b, d|ax+by / a+b
// 求两个正整数 a 和 b 的 最大公约数 d
// 则有 gcd(a,b) = gcd(b,a%b)
//    证明:
//        设a%b = a - k*b 其中k = a/b(向下取整)
//        若 d 是 (a,b) 的公约数 则知 d|a 且 d|b 则易知 d|a-k*b 故d也是 (b,a%b) 的公约数
//        若 d 是 (b,a%b) 的公约数 则知 d|b 且 d|a-k*b 则 d|a-k*b+k*b = d|a 故而 d|b 故而 d 也是 (a,b) 的公约数
//        因此 (a,b) 的公约数集合和 (b,a%b) 的公约数集合相同, 所以他们的最大公约数也相同
#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main()
{
    int n;
    scanf("%d", &n);
    
    while (n -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", gcd(a, b));
    }
    return 0;
}