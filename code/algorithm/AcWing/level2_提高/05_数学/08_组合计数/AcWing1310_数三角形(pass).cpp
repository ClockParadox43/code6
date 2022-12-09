// 矩形, 长宽格点分别有 n,m 个, 端点分别有 n+1, m+1 个
// 
// 例子: 假设总共的格点数为 9, 三角形一共有 3 个点, 总共的方案数就是 C(9,3), 还得去掉不合法的方案数 
// 斜率正无穷: (m + 1) * C(n+1,3) 
// 斜率为 0: (n + 1) * C(m+1, 3)
//
// 横坐标是 i, 纵坐标是 j
// 斜率存在且不为 0: 由两个端点 A,B 组成的横坐标之差是 i, 纵坐标只差是 j 的线段共有 2(n-j+1)(m-i+1)个 (正反斜率, 所以乘 2) 
//                  对于每一条斜率上共有 gcd(i,j)+1 个端点, 减去 A, B 两个端点, 即第三个点有 gcd(i,j)-1 种满足度情况 
//                  因此总方案数是 2(gcd(i,j)-1) * (n-j+1) * (m-i+1) 
//
// i, j枚举的是红色斜线的宽度和高度, (n-i)*(m-j) 表示左下角的点可以放的位置个数
// gcd(i,j)公式中: (i,j)的含义是 (左下角点和右上角点的横坐标之差, 纵坐标之差)
// gcd(i,j) 表示斜边上除了端点的坐标为整数的点个数, 例如: (2,1) 和 (8,4) 之间的整数点个数为 gcd(6,3) - 1 = 2
#include <iostream>

using namespace std;

typedef long long LL;

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

LL C(int n)
{
    return (LL)n * (n-1) * (n-2) / 6;
}

int main()
{
    int n, m; scanf("%d%d",&n, &m);
    n ++ , m ++ ;       // 转化为格点数
    
    LL res = C(n * m) - (LL)n * C(m) - (LL)m * C(n);
    
    // 枚举横坐标之差 i, 纵坐标之差 j
    for (int i = 1; i <= n; ++ i )
        for (int j = 1; j <= m; ++ j )
            res -= 2ll * (gcd(i, j) - 1) * (n - i) * (m - j);

    cout << res << endl;
    return 0;  
}