// 三维凸包一般指面积对小凸包, 二维一般指周长最小
// 面积相当于求三角形面积, 也就可以想到用叉积来求, 这和求二维凸包是一样的
#include <iostream>
#include <algorithm>
#include <cmath>

#define _x first;
#define _y second;

using namespace std;

const int N = 210;   // 面是 2 倍的 n 减 4
const double eps = 1e-10; // 抖动会使精度变低, 那么精度(eps)就要定的稍微高些

int n, m;   // n:点个数, m:三维凸包的面积
bool g[N][N];   // 表示每个边所在的面有没有被覆盖到

// 相除可以得到 0~1 之间的数, 减去一个 0.5 就可以得到一个 [-0.5, 0.5] 之间的数 再乘上一个步长(eps)就是一个非常小的扰动
double rand_eps()
{
    return ((double)rand() / RAND_MAX - 0.5) * eps;
}

// 为了防止所有点出现四点共面的情况, 我们将所有点做一个微小抖动
//      - 这里判断正负不能进行约等于的操作(sign(), dcmp()), 对所有点做一个微小抖动
//        (抖动的目的就是让之前 4 点共面的点变得不共面)
//        附加一定偏移量, 如果进行了约等于的操作就相当于抵消了这些微小抖动
//        
struct Point // 点
{
    double x, y, z;
    void shake() { x += rand_eps(), y += rand_eps(), z += rand_eps(); } // 增加微小抖动
    
    Point operator- (Point b)       // 三维向量减法
    {
        return {x - b.x, y - b.y, z - b.z};
    } 

    Point operator+ (Point b)       // 三维向量加法
    {
        return {x + b.x, y + b.y, z + b.z};
    }

    Point operator* (Point b)       // 三维向量叉积(叉积乘的是行列式), 返回向量
    {
        return {y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x};
    }

    double operator& (Point b)      // 一般用 '&' 表示点积, 点积返回数值
    {
        return x * b.x + y * b.y + z * b.z;
    } 

    double len()   // 一个向量的模长, 点积/向量n
    {
        return sqrt(x * x + y * y + z * z);
    }
}q[N];  
struct Plane
{
    int v[3];   // 一个面用三个点表示
    
    // 我们需要判断一个点是在面上还是在面下, 因此需要求这个面的法向量
    Point norm() 
    {
        // 3 个点是逆时针方向的 3 个点
        //     2
        //    /
        //   / 
        // 0/_______ 1 
        return (q[v[1]] - q[v[0]]) * (q[v[2]] - q[v[0]]);   // 法向量 平面上两个向量的叉积
    }

    double area() // 求面积, 叉积的模长就是面积, 所以返回 反向法向量 / 2
    {
        return norm().len() / 2;
    }

    bool above(Point a)   // 判断点在上方还是在下方
    {
        return ((a - q[v[0]]) & norm()) >= 0;      // 平面上任意取一点 点乘上法向量判断是否大于等于 0
    }
}plane[N], np[N];   // np[]: 备份数组

void get_convex_3d()    
{
    // 最开始时只有 2 个面, 将前 3 个点变成 2 个面(正面, 背面)
    //    2      2
    //   /        
    // 0/__ 1  0   1
    //  逆时针   顺时针
    // 
    // 将数字想象成一圈, 一个逆时针, 一个顺时针
    plane[m ++ ] = {0, 1, 2};
    plane[m ++ ] = {2, 1, 0};
    
    // 从第 4 个点开始看
    for (int i = 3; i < n; ++ i )
    {
        int cnt = 0;
        for (int j = 0; j < m; ++ j ) // 检查每一个面
        {
            bool t = plane[j].above(q[i]);  // 判断当前点在第 j 个平面的上方还是下方
            if (!t) np[cnt ++ ] = plane[j]; // 若覆盖不到则保留
            for (int k = 0; k < 3; ++ k )   // 记录面上的 3 个边, mod 3 使数据保持在 0~2 上, 0->1, 1->2, 2->0 
                g[plane[j].v[k]][plane[j].v[(k + 1) % 3]] = t; // 标记每一条边是否被照射
        }

        for (int j = 0; j < m; ++ j)       // 检查每一个面
            for (int k = 0; k < 3; ++ k )  // 枚举所有边
            {
                int a = plane[j].v[k], b = plane[j].v[(k + 1) % 3];
                if (g[a][b] && !g[b][a])  np[cnt ++ ] = {a, b, i};  // 只被照射到一个面的边将与当前点组成新面(注意是逆时针方向)
            }

        // 将新的凸包赋值给圆凸包
        m = cnt;
        for (int j = 0; j < m; j ++ ) plane[j] = np[j]; // 更新当前的所有面
    } 
}

int main()
{
    scanf("%d", &n);    // 读入所有点数
    for (int i = 0; i < n; ++ i )   // 读入所有点
    {
        scanf("%lf%lf%lf", &q[i].x, &q[i].y, &q[i].z);
        q[i].shake();
    }

    get_convex_3d();    // 求出三维凸包

    double res = 0; // 求面积
    for (int i = 0; i < m; ++ i )
        res += plane[i].area();
    printf("%lf\n", res);

    return 0;
}