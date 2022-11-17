#include <iostream>

using namespace std;

const int N = 100010;

int stk[N], tt;

// 输出每个数左边第一个比它小的数, 如果不存在则输出 −1
// 也就是说左边
int main()
{
    int n;
    scanf("%d", &n);
    
    while (n -- )
    {
        while (tt && stk[tt] >= x) tt -- ;    // 如果栈顶元素小那么当前的 x 就找到目标值
        if (!tt) printf("-1 ");
        else printf("%d", stk[tt]);
        stk[ ++ tt] = x;
    }

    return 0;
}