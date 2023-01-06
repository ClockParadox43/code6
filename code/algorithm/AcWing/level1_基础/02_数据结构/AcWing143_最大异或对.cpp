#include <iostream>

using namespace std;
// 思路:二进制主要特点就是二进制表示下不进位, 所以参与的运算符独立
//      所以可以从低到高依次考虑 x 的每一位是填写 0 还是填 1
// 
// 每个单词最大长度为 2^31
// 一般情况下都比三百万小
const int N = 100010, M = 3000000;

int n;
// 最大异或和不是 0 就是 1
int son[M][2], idx;
int a[N];

void insert(int x)
{
    int p = 0;
    // -1 在二进制里代表的是 11111..., 所以 ~i 代表的是 0
    for (int i = 30; ~i; -- i ) // 将高位优先存在上面
    {
        int& s = son[p][x >> i & 1];    // (x >> i & 1) : 将 x 拆解成二进制后插入
        if (!s) s = ++ idx;
        p = s;
    }
}


int query(int x)
{
    int res = 0, p = 0;             // 每次 x 都要找和自己异或最大的路径, 每个 a[i] 都枚举
    for (int i = 30; ~i; -- i)
    {
        int u = x >> i & 1;         // 取出 x 的第 i 位, 如果第 i 位置是 0 那我就要 1 
        if (son[p][!u])             // u 为 0, !u 就是 1, 如果存在那就贡献一位 1, u = 1, 就要找 0, 相异为 1, 找和自己不同的数即可
        {                           
            res += 1 << i;          // 只要碰到相异的就说明有 1, 每次往下走一层, 看看当前层是否有合适的位置
            p = son[p][!u];
        }
        else p = son[p][u];
    }
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i )
    {
        scanf("%d", &a[i]);
        insert(a[i]);
    }

    // 让没个数都去找一个对于自己最大的异或队
    // 最大中求最大
    int ans = 0;
    for (int i = 0; i < n; ++ i )       
        ans = max(ans, query(a[i]));   
    printf("%d", ans);

    return 0;
}