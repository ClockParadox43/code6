#include <iostream>
#include <cstring>

using namespace std;

const int N = 200003, null = 0x3f3f3f3f;

int h[N];

// 开放寻址法
// 如果 find 函数在 h 中不存在的话, 返回的是应该存的位置
int find(int x)
{
    // 有位置来到该位置
    // 没有来到下一个坑位置
    int k = (x % N + N) % N;
    while (h[k] != null && h[k] != x) // 没找到 x 就一直循环
    {
        ++ k;
        if (k == N) k = 0;   // 看完最后一个坑位, 循环看第一个坑位
    }
    return k;
}

int main()
{
    int q; scanf("%d", &q);
    memset(h, 0x3f, sizeof h);
    
    while(q -- )
    {
        char op[2]; 
        int x;
        scanf("%s%d", op, &x);
        // 插入就是为 x 找一个坑位
        int k = find(x);
        if (*op == 'I') h[k] = x;
        else 
        {
            // 如果有这个数, 一定是 % N 同余的那下块区域内没有 0x3f (碰到就说明该数没有)
            // 因为有 k 就会枚举式往后跳
            if (h[k] != null) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}