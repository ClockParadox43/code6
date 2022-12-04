// 先手必胜状态: 通过某种方式先手拿完后剩下的状态是先手必胜状态
// 先手必败状态: 不管怎么操作剩下的状态都是必胜状态 (都是对方胜利)
//
// 如果异或和不是 0 , 一定有方式拿走若干石子, 让异或值变成 0
#include <iostream>

using namespace std;

int main()
{
    int n; scanf("%d", &n);
    int ans = 0;
    for (int i = 1; i <= n; ++ i )
    {
        int x; scanf("%d", &x);
        ans ^= x;
    }    
    if (ans) puts("Yes");
    else puts("No");

    return 0;
}