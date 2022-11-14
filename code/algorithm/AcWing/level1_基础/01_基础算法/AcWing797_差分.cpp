// 前缀和的逆运算
// 实现 ai = b1 + ... bi
// 构造完后使得 a[] 是 b[] 的前缀和
// b [ 3 2 0 -2 -3 ] 差分
// a [ 3 5 5  3  0 ] 前缀和
//     0 1 2  3  4
//
// a[] 是 b[] 的前缀和, b[] 就是 a[] 的差分
// 
// 也很多这样的操作: 在 a[] 的 (l,r) 区间内全部加上 c
// 也就是让 b(差分数组) + c, 但是 bl+c 的效果是 al~an 自动加上 c
// (生成前缀和的时候, a[] 会遍历累计 b[] 数组) 
// 
// b[] 遍历一遍求出原来的前缀和
// bl+c, al...an就会自动 +c
//
// 和线段树区别, 这个是离线查询, 线段树是在线查询
#include <iostream>

using namespace std;

const int N = 100010;

int n, m;
// a : 前缀和数组
// b : 差分数组
int a[N], b[N];

// 起始位置 + c, 终点位置 - c  
void insert(int l, int r, int c)
{
    b[l] += c;
    b[r + 1] -= c;          // 减 c 的作用是从 r+1 开始后面都减去 c
}

void test()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i ) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++ i ) insert(i, i, a[i]);  // 生成原数组 : 从起始位置每个数字 +c, 终点位置 -c,
                                                        // b 数组加一遍就能还原回 a 数组
    
    // 查询操作
    while (m -- )
    {
        int l, r, c;
        scanf("%d%d%d", &l, &r, &c);
        insert(l, r, c);
    }
    
    // 生成前缀和数组
    for (int i = 1; i <= n; ++ i ) b[i] += b[i - 1];
    for (int i = 1; i <= n; ++ i ) printf("%d ", b[i]);
}

int main()
{
    test();
    return 0;
}