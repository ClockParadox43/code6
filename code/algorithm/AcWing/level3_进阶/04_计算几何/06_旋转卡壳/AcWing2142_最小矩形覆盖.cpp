// 旋转卡壳这个算法一定要落实到边上
// 所有点的最小矩形一定是唯一的
//
// 最小矩形所有边上一定有凸包上的点
// 当定完点后, 矩形的角度有无穷多种, 所以光定完点是不够的, 还要定义边
// 用平行线将矩形卡出来, 证明见图
//
// 所有矩阵性质:
//  1. 每条边上必有凸包上的点
//  2. 矩形上的边与凸包的某条边共线
// 所以现在只需要枚举以凸包上的每条边为矩形的一边所构成的矩形, 利用旋转卡壳
// 求出对于每条边的另外三个点, 然后求出当前矩形的长度来确定面积, 最后确定矩形的四个顶点即可
//  - 求距离凸边形最远的边(平行线旋转卡壳, 差积求面积)
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;
const int N = 50010;
const double eps = 1e-12, INF = 1e20;
const double PI = acos(-1);

int n;
PDD q[N];
PDD ans[N];
double min_area = INF;  
int stk[N], top;    // 求凸包
bool used[N];

int sign(double x)
{
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

int dcmp(double x, double y)
{
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}



PDD operator+ (PDD a, PDD b)        // 向量加法
{
    return {a.x + b.x, a.y + b.y};
}

PDD operator- (PDD a, PDD b)        // 向量减法
{
    return {a.x - b.x, a.y - b.y};
}

PDD operator* (PDD a, double t)     // 向量乘法
{
    return {a.x * t, a.y * t};
}

PDD operator/ (PDD a, double t)     // 向量除法
{
    return {a.x / t, a.y / t};
}

double operator* (PDD a, PDD b)     // 叉乘
{
    return a.x * b.y  - a.y * b.x;
}

double operator& (PDD a, PDD b)      // 点乘
{
    return a.x * b.x + a.y * b.y;
}

double area(PDD a, PDD b, PDD c)     // 面积
{
    return (b - a) * (c - a);
}

double get_len(PDD a)   // 求向量模长
{
    return sqrt(a & a);
}

double project(PDD a, PDD b, PDD c)  // 向量投影
{
    return ((b - a) & (c - a)) / get_len(b - a);
}

PDD norm(PDD a)     // 单位向量
{
    return a / get_len(a);
}

PDD rotate(PDD a, double b)     // 求两个向量之间角度
{
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}

// 找凸包
void andrew()
{
    sort(q, q + n);
    for (int i = 0; i < n; i ++ )
    {
        while (top >= 2 && sign(area(q[stk[top - 2]], q[stk[top - 1]], q[i])) >= 0)
            used[stk[ -- top]] = false;
        stk[top ++ ] = i;
        used[i] = true;
    }
    used[0] = false;
    for (int i = n - 1; i >= 0; i -- )
    {
        if (used[i]) continue;
        while (top >= 2 && sign(area(q[stk[top - 2]], q[stk[top - 1]], q[i])) >= 0)
            top -- ;
        stk[top ++ ] = i;
    }
    reverse(stk, stk + top);
    top -- ;
}


void rotating_calipers()
{
    // a为最远的点, b为右边的点, c为左边的点
    // d, e 两点形成的边
    // b(投影): b 的初始值详看 "注意"
    for (int i = 0, a = 2, b = 1, c = 2; i < top; ++ i )
    {
        auto d = q[stk[i]], e = q[stk[i + 1]];
        
        // 对比面积, 找到最远的点
        while (dcmp(area(d, e, q[stk[a]]), area(d, e, q[stk[a + 1]])) < 0) 
            a = (a + 1) % top;

        // 对比投影长度
        // 找到右边最远的点
        while (dcmp(project(d, e, q[stk[b]]), project(d, e, q[stk[b + 1]])) < 0) 
            b = (b + 1) % top;
        
        // c 开始需要从 a 开始, 因为 c 一定在 a 的逆时针, 这样才可以找单峰函数
        if (!i) c = a;
        
        // 找到左边最远的点(负数)
        while (dcmp(project(d, e, q[stk[c]]), project(d, e, q[stk[c + 1]])) > 0) 
            c = (c + 1) % top;
        
        auto x = q[stk[a]], y = q[stk[b]], z = q[stk[c]];
        
        // 求高和底
        auto h = area(d, e, x) / get_len(e - d);
        auto w = ((y - z) & (e - d)) / get_len(e - d);

        // 如果可以更新最小值
        if (h * w < min_area) 
        {
            min_area = h * w;
            ans[0] = d + norm(e - d) * project(d, e, y); // 右下角
            ans[3] = d + norm(e - d) * project(d, e, z);
            auto u = norm(rotate(e - d, -PI / 2));       // 向上的法向量(逆时针旋转PI/2)标准化。
            ans[1] = ans[0] + u * h;
            ans[2] = ans[3] + u * h;
        }
    }
}

int main()
{
    // 第一行包含一个整数 n, 表示点的数量
    // 接下来 n 行, 每行包含两个用空格隔开的浮点数, 表示一个点的 x 坐标和 y 坐标
    // 不用科学计数法, 但如果小数部分为 0, 则可以写成整数
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%lf%lf", &q[i].x, &q[i].y);
    andrew();
    rotating_calipers();



    // 先输出 y 坐标最小的顶点的 x,y 坐标, 如果有两个点的 y 坐标同时达到最小, 则先输出 x 坐标较小者的 x,y 坐标
    // 然后, 按照逆时针的顺序输出其他三个顶点的坐标
    // 
    // 从第 0 个点开始输出, 优先输出较小的, (i < k; k = i)
    // 或者 如果纵坐标一样 且 相等就用横坐标进行对比
    int k = 0;
    for (int i = 1; i < 4; i ++ )
        if (dcmp(ans[i].y, ans[k].y) < 0 || !dcmp(ans[i].y, ans[k].y) && dcmp(ans[i].x, ans[k].x) < 0)
            k = i;

    printf("%.5lf\n", min_area);
    for (int i = 0; i < 4; i ++, k ++ )
    {
        auto x = ans[k % 4].x, y = ans[k % 4].y;
        // 例如-0.000000要变成0.000000
        if (!sign(x)) x = 0;
        if (!sign(y)) y = 0;
        printf("%.5lf %.5lf\n", x, y);
    }
}