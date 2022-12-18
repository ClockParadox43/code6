// 望远镜的视野可以描述为一个圆, 其圆心位于原点, 半径为 R
// 飞行物可视作一个 N 个顶点的简单多边形
// Updog 希望知道飞行物处于望远镜视野之内的部分的面积
#include <iostream>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;
const int N = 55;
const double eps = 1e-8;        
// eps 往大猜, 中间有一步求圆心到线段最短距离, 判断点是否在线段内
// 判断线段内: 1) 判断三点是否共线(叉积)
//               叉积是有误差的, 如果 eps 定义的很小, 误差就比较大
//               共线就有可能误判成不共线, 情况三角形的位置就会判断错
const double PI = acos(-1);

double R;  // 半径
int n; 
PDD q[N], r;   // 存储所有点, r:圆心

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

PDD operator+ (PDD a, PDD b)
{
    return {a.x + b.x, a.y + b.y};
}

PDD operator- (PDD a, PDD b)
{
    return {a.x - b.x, a.y - b.y};
}

PDD operator* (PDD a, double t) // 数乘
{
    return {a.x * t, a.y * t};
}

PDD operator/ (PDD a, double t) // 数除
{
    return {a.x / t, a.y / t};
}

double operator* (PDD a, PDD b) // 叉积
{
    return a.x * b.y - a.y * b.x;
}

double operator& (PDD a, PDD b) // 点积
{
    return a.x * b.x + a.y * b.y;
}

double area(PDD a, PDD b, PDD c)
{
    return (b - a) * (c - a);
}

double get_len(PDD a)   // 模长|a|
{
    return sqrt(a & a);
}

double get_dist(PDD a, PDD b)
{
    return get_len(b - a);
}

// 求 ab 在 ac 投影的长度
// 向量c · 向量b / |a|
double project(PDD a, PDD b, PDD c)
{
    // c-a,b-a:求的是向量 c, b
    return ((c - a) & (b - a)) / get_len(b - a);
}

// 逆时针旋转一个角度, 行列式
PDD rotate(PDD a, double b)
{
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}

// 单位向量
// 向量 {a.x / t, a.y / t} 
PDD norm(PDD a)
{
    return a / get_len(a);
}

// 判断一个点是否在线段上
// p-a:算的是向量
// !sign((p - a) * (p - b)): 在线段上首先面积是 0 
// sign((p - a) & (p - b)) <= 0: 在线段左/右边, 还是在线段内, 在线段内就是小于 0 
bool on_segment(PDD p, PDD a, PDD b)
{
    return !sign((p - a) * (p - b)) && sign((p - a) & (p - b)) <= 0;
}

// 取交点
PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w)
{
    auto u = p - q;
    auto t = w * u / (v * w);
    return p + v * t;
}

// 求圆和直线的交点
// 交点存到 pa, pb 中
//      e
//  /.__.__.|
//   a  /  b
//     .r
double get_circle_line_intersection(PDD a, PDD b, PDD& pa, PDD& pb)
{
    // e: 交点
    // a: 起点
    // b-a: 终点
    // r: 另一个向量起点是 r
    // rotate(b - a, PI / 2): 返回 线段ab 逆时针旋转 90° 后的坐标 
    // get_line_intersection: 求两个线段之间的交点 e
    auto e = get_line_intersection(a, b - a, r, rotate(b - a, PI / 2));
    
    // mind: r 到直线(交点e)的距离
    auto mind = get_dist(r, e);

    // 判断 e 是否在直线 ab 上, e 可能不在直线上(线段ab 可能在圆外边)
    // 如果 e 不在在直线 ab 上, 那么 re 的最短距离就是到 ab 两个端点的最短距离
    if (!on_segment(e, a, b)) 
        mind = min(get_dist(r, a), get_dist(r, b));
        
    // 如果半径小于 re 的距离, 那么他们就没有交点
    if (dcmp(R, mind) <= 0)
        return mind;    // 直接返回 re 的距离

    // 否则就求下 垂足re到圆的交点长度
    // 已经有了交点e(有了r到e的距离) 和 半径 就用勾股定理 求出另一条边的长度
    // 半径的平方 - 垂足的平方
    // ps: 这里 re 的距离不能换成 mind, mind 的值可能更新出成 r->a/b 的距离
    auto len = sqrt(R * R - get_dist(r, e) * get_dist(r, e));

    // e:起点
    // 求出单位向量, 返回 mind
    pa = e + norm(a - b) * len;
    pb = e + norm(b - a) * len;
    return mind;
}

// 求 向量a 向量b 两个向量围成的有向扇形面积
double get_sector(PDD a, PDD b)
{
    // 先求出 角度θ
    // a 和 b 是线段, 所以它和圆心的端点是小于 pi 的
    auto angle = acos((a & b) / get_len(a) / get_len(b));
    // 如果是逆时针转就是正的, 如果是顺时针转就是负数
    if (sign(a * b) < 0) angle = -angle;
    return R * R * angle / 2;
}

// 求圆和三角形交集的有向面积
double get_circle_triangle_area(PDD a, PDD b)
{
    // 用 a 和 r(圆心) 的距离, 用 b 和 r(圆心) 的距离
    auto da = get_dist(r, a), db = get_dist(r, b);

    // 情况1:
    // R 是半径 (说明在三角形内)
    // R >= da && R >= db 返回三角形的有向面积(向量a x 向量b / 2)
    if (dcmp(R, da) >= 0 && dcmp(R, db) >= 0) return a * b / 2;

    // 返回三点共线的情况
    // 向量a x 向量b = 0, 返回 0
    if (!sign(a * b)) return 0;

    // pa 和 pb 表示 直线 和 圆的两个交点, pa 是距离 a 更近的点, pb 是距离 b 更近的点
    // mind: 求出半径到线段的最短距离
    PDD pa, pb;
    auto mind = get_circle_line_intersection(a, b, pa, pb);

    // 情况2: 如果半径小于最短距离(R <= mind), 返回从 r 到 a 和 b 的向量扇形面积  
    //        - 线段ab 与 圆无交点
    // 无交点在情况2 就返回了
    if (dcmp(R, mind) <= 0) return get_sector(a, b);

    // 情况3: R >= da
    //        - 线段ab 与圆有交点且 a 在圆内
    // 线段 ab 与圆有交点, 且 a 在圆内
    // a * pb / 2: 三角形面积
    // get_sector(pb, b): 扇形面积
    if (dcmp(R, da) >= 0) return a * pb / 2 + get_sector(pb, b);

    // 情况4: 线段ab 与圆有交点且 b 在圆内
    if (dcmp(R, db) >= 0) return get_sector(a, pa) + pa * b / 2;

    // 情况5: 线段ab 与圆有交点且 ab 都在圆外 
    return get_sector(a, pa) + pa * pb / 2 + get_sector(pb, b);
}

double work()
{
    double res = 0;
    
    // get_circle_triangle_area:圆和三角形的面积并
    for (int i = 0; i < n; i ++ )
        res += get_circle_triangle_area(q[i], q[(i + 1) % n]);
    return fabs(res);
}

int main()
{
    // 本题包含多组测试数据
    // 对于每组数据, 第一行包含一个实数 R
    // 第二行包含一个整数 N
    // 接下来 N 行, 每行包含两个实数 xi,yi, 表示一个顶点的坐标, 相邻两行描述的顶点在多边形中也是相邻的

    // 读入半径和点数
    while (scanf("%lf%d", &R, &n) != -1) 
    {   
        // 读入所有点数
        for (int i = 0; i < n; ++ i ) scanf("%lf%lf", &q[i].x, &q[i].y);    
        
        // 要将答案去取绝对值, 因为给的是顺指针方向的多边形还是逆时针方向的是不确定的
        printf("%.2lf\n", work());   
    }     

    return 0;
}