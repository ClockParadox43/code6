// 在二维平面内有 n 条线段, 请你编写一个程序, 判断是否存在一条直线满足将这 n 条线段投影到该直线上后, 所有的投影线段至少具有一个公共点
//
// 投影到线段的公共点其实就是关于该点做垂线, 整个空间能投影到该点上所构成的垂线
// 因此原问题如果有解必然能构成一条直线穿过所有线段
//
// 计算几何常见技巧:
//      枚举两两线段的各个端点, 连一条直线, 再判断剩下的线段是否和这条直线有交点
// 
//      引: 我们可以枚举直线旋转的位置, 线段长度必然有限, 旋转到一定程度会 '卡' 住某个端点
//          卡主那个端点继续旋转, 一定会被第二条线段卡住, 如果那条直线符合穿过所有线段就是符合要求的答案 
// 
//      解: 所以我们可以枚举所有点对, 看下所枚举到的点对卡出的直线是否穿过所有线段
//          如何判断直线是否穿过所有线段: 做一半跨立实验, 在直线上任意取一个向量, 判断线段上两个点是否在向量两侧
//          如果相交叉乘后得到的面积必然小于 0, 所以判断两个向量共同面积的的乘积是否小于 0
//
// 我们就得到了一个结论:
// 任何一个可行解直线都可以转换成一条 过 这 n 个线段的 2n 个端点中的两个端点 的直线
// 所以我们只要看所有过线段两个端点的直线中有没有解就可以判定是否有解
// 
// 时间复杂度:
// 枚举两个点(N^2), 再去枚举其他所有线段(N)
// O(N^3)

#include <iostream>
#include <cmath>

#define x first
#define y second
using namespace std;

const double eps = 1e-8; 
typedef pair<double, double> PDD;       // 输入为浮点数
const int N = 210;      // 每个线段有两个点, 所以一共需要 2n 个点

int n;
PDD q[N], a[N], b[N];   // q[]: 所有点, a[],b[]:表示线段两个端点


int cmp(double x, double y)     // 比较函数
{
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;  
}

int sign(double x)  // 符号函数 - 判断浮点数的精度
{
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

// double area(PDD a, PDD b, PDD c)
// {
//     return cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
// }

double cross(double x1, double y1, double x2, double y2)
{
    return x1 * y2 - x2 * y1;
}

double area(PDD a, PDD b, PDD c)
{
    double ab_x = b.x - a.x;
    double ab_y = b.y - a.y;

    double ac_x = c.x - a.x;
    double ac_y = c.y - a.y;

    return cross(ab_x, ab_y, ac_x, ac_y);
}

// 原代码: ab和j ij 的位置写反了
bool check()
{
    // 所有点对 
    for (int i = 0; i < n * 2; ++ i )           
        for (int j = i + 1; j < n * 2; ++ j )   // a->b, a<-b 是一样的, 可以保序列, 所以 b 从 i + 1 开始枚举即可  
        {
            if (!cmp(q[i].x, q[j].x) && !cmp(q[i].y, q[j].y)) continue;     // 横纵坐标一样说明是同一个点, 跳过即可
            // 枚举所有线段判断是否满足要求, 也就是判断面积的乘积是否小于 0
            bool flag = true; 
            for (int k = 0; k < n; ++ k )
            {
                if (sign(area(q[i], q[j], a[k])) * sign(area(q[i], q[j], b[k])) > 0)
                {
                    flag = false;       // 如果 > 0, 说明两个向量再直线的同一侧, 不能穿过这条线段
                    /*
                            穿过的情况：
                                    q[i]
                                    |
                                    |
                           a[k].....|.....b[k]
                               \    |     /
                                \   |    /
                                 \  |   /
                                  \1| 2/
                                   \| /
                                  q[j]
                          其中角1和角2 即夹角, 根据右手螺旋即可判断：逆时针为负, 顺时针为正
                    */
                    break;
                }
            }
            if (flag) return true; 
        }
    return false;
}

int main()
{
    // 第一行包含整数 T, 表示共有 T 组测试数据, 每组数据第一行包含整数 n, 表示共有 n 条线段
    // 接下来 n 行, 每行包含四个实数 x1,y1,x2,y2, 其中 (x1,y1) 和 (x2,y2) 是一条线段的两端点坐标
    int T; scanf("%d", &T);
    while (T -- )
    {
        scanf("%d", &n);
        for (int i = 0, k = 0; i < n; ++ i )
        {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            q[k ++ ] = {x1, y1}, q[k ++ ] = {x2, y2};
            a[i] = {x1, y1}, b[i] = {x2, y2};               // a[],b[]:表示线段两个端点
        }

        if (check()) puts("Yes!");
        else puts("No!");
    }
    return 0;
}

