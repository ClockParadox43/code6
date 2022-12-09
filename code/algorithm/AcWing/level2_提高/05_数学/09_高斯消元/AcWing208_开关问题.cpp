// 这里以一个例子讲解这个题目, 有三个开关, 分别为 1、2、3
// 规则是: 如果按 1, 则 1、2 的状态会改变
//        如果按 2, 则 1、2、3 的状态会改变
//        如果按 3, 则 3 的状态会改变.
// 则始状态是 0、0、0, 转变为 1、1、1 存在多少种方案 ?
//
// 方程消元详细过程可以看直播 1.14
// 思考: 要使第 1 个开关变化, 哪些开关会对第 1 个开关产生影响
//          - 1 和 2 开关会对第一个开关产生影响
//
// x₁^x₂ = 1  => 1 个 2 两个开关, 异或后结果是 1, 才能保证第一个开关会变一下
// x₁^x₂ = 2  => 1 和 2 能影响到 2
// x₃^x₂ = 3  => 2 和 3 能影响到 3

#include <iostream>
#include <cstring>

using namespace std;

const int N = 35;

int n;
int a[N][N]; 

int gauss()
{
    // 因为不能保证有解, r 和 c 会定义到外边, 之后可能还会用到
    int r, c;
    for (r = 1, c = 1; c <= n; c ++ )
    {
        int t = r;  // 找主元
        for (int i = r + 1; i <= n; ++ i )
            if (a[i][c]) 
                t = i;

        if (!a[t][c]) continue; // 不保证唯一解 --- 不一定有主元

        // 交换主元行至 r 行
        for (int i = c; i <= n + 1; ++ i ) swap(a[t][i], a[r][i]);

        // 用第 r 行的 a[r][j] 消 i 行的 a[i][j] 前提是第 i 行的最左边是 1(有主元)
        for (int i = r + 1; i <= n; ++ i )
            for (int j = n + 1; j >= c; -- j )  
                a[i][j] ^= a[i][c] & a[r][j];   // 等价于 if(a[i][c]) a[i][j]^=a[r][j]
        
        // 不能写 a[i][j] ^= a[i][r] & a[r][j]
        // 是因为可能存在中间无主元的情况, 此时 r 不 ++ 了, c 还在循环中 ++, 导致 r != c
        ++ r;
    }

    int res = 1;
    //此时已经到了全零行
    if (r < n + 1)
    {
        for (int i = r; i <= n; i ++ )
        {
            // 全零行的右边出现非零 无解
            if (a[i][n + 1]) return -1;  // 出现了 0 == !0，无解
            res *= 2;
        }
    }
    return res;
}

int main()
{
    int T; scanf("%d", &T);
    while (T -- )
    {
        memset(a, 0, sizeof a);
        scanf("%d", &n);
        
        for (int i = 1; i <= n; ++ i ) cin >> a[i][n + 1];  // 读入每个灯最开始的 初始状态
        
        // 读入每个灯的最终状态 
        for (int i = 1; i <= n; ++ i )
        {
            int t; 
            scanf("%d", &t);
            a[i][n + 1] ^= t;   // 关心 a[i][n + 1](初始状态) 和 t(新状态) 是否发生变化
                                //    - ps:异或后如果两灯没有变化就是 0(初始状态就是 0), 变化了就是 1

            a[i][i] = 1;        // 每个开关可以控制自己(自己按了也会变设置为 1)
        }

        // 读入后续相关操作, 读到 0 为止
        // 思考: 系数矩阵中, 如果按第 x 个开关, 第 y 个开关也会亮, 系数矩阵中应该变化哪个值
        // 第 y 个灯表示第 y 个方程, 第 y 个方程会影响第 x 个系数, 因为按的是第 y 个方程中的第 x 个开关
        int x, y;
        while (scanf("%d%d", &x, &y), x || y) a[y][x] = 1;
        // 第 y 个等式(行)的右边(开关 y 状态) 左边(操作开关 x)(第 x 列)的系数等于 1
        
        int t = gauss();
        if (t == -1) puts("Oh,it's impossible~!!");
        else printf("%d\n", t);
    }
    return 0;
}