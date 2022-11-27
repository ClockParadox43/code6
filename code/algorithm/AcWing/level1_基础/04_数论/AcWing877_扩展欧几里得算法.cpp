// 裴蜀定理:
// 若 a,b 是整数, 且 gcd(a,b)=d, 那么对于任意的整数 x,y,ax+by 都一定是 d 的倍数 
// 特别地, 一定存在整数 x,y, 使 ax+by=d 成立
// 它的一个重要推论是: a,b 互质的充分必要条件是存在整数 x,y 使 ax+by=1
#include <iostream>

using namespace std;

int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0) 
    {
        x = 1, y = 0; 
        return a;
    }
    int x1, y1, res;
    res = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return res;
}
int main()
{
    int q, a, b, x, y;
    scanf("%d", &q);
    while (q -- )
    {
        scanf("%d%d", &a, &b);
        exgcd(a, b, x, y);
        printf("%d %d", x, y);
    }
    return 0;
}