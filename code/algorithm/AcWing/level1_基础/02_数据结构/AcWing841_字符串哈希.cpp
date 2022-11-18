// 全称字符串前缀哈希法, 把字符串变成一个p进制数字(哈希值), 实现不同的字符串映射到不同的数字
// 对形如 X1 X2 X3...Xn−1 Xn 的字符串, 采用字符的 ascii 码乘上 P 的次方来计算哈希值
// 
// 
// 因为是从 1 开始计算的, 所以第 0 位是 r-1
// h[r] 代表第 0 位, r-1 
// h[l-1] 代表高位, l-2

#include <iostream>

using namespace std;

typedef unsigned long long ULL;  // 溢出相当于直接取模 
const int N = 1e5 + 5, P = 131;

ULL h[N], p[N];     // h[]:前缀和数组, p[]:字符串数组

// h[i] 前 i 个字符的 hash 值
// 字符串变成一个 p 进制的数字, 体现了字符 + 顺序, 需要确保不同的字符串对应不同的数字
// P = 131 或  13331 Q=2^64，在 99% 的情况下不会出现冲突
// 使用场景: 两个字符串的子串是否相同

ULL query(int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];  // 区间和公式, l 需要进行数学性质上的左移
}

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    string x;
    cin >> x;

    // 字符串从1开始编号，h[1]为前一个字符的哈希值
    p[0] = 1;
    h[0] = 0;
    for (int i = 0; i < n; ++ i )
    {
        p[i + 1] = p[i] * P;
        h[i + 1] = h[i] * P + x[i]; // 前缀和求整个字符串哈希值 
    }

    while (q -- )
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if (query(l1, r1) == query(l2, r2)) printf("Yes\n");
        else printf("No\n"); 
    }

    return 0;
}
