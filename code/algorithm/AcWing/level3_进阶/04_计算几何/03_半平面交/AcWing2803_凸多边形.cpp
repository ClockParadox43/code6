// 求半平面交步骤:
//      1.将所有边按角度排序
//      2.利用双端队列维护平面交的所有边(也是半平面交的轮廓), 按顺序扫描所有的向量
//      3.检查队尾直线和队尾前一条的交点是否在当前边的右边,  如果在右边则将元素踢出队列(角度相同的向量也踢出去)
//      4.对于队头重复 3
//      5.最后队列中的所有直线就是构成最终半平面交的边集
//      6.相邻两边的交点就是最终半平面交的所有顶点
//
// 注意点: 
//      1) 直线的角度就是向量的角度, 向量在 mod 2π 的空间中
//          - 三角函数中 pai(π) 常指角度, 即以 "弧度" 为角度单位时, 一个整圆周的对应角度就是 "2π弧度", 也就相当于通常的 "360°角度". 
//            三角函数数值以 "2π" 为一个周期出现, 一个完整的三角函数图像显示角度从0到2π之间的函数值. 
//         (0,2π], (-π,π]: 左闭右开左开右闭都可以 
// 
//      2) 求两条向量夹角用 rotate(用矩阵求的那个)会很好用, 求一个向量角度用 atan2 的函数
//         atan2: 求出的角度范围将平面上所有的向量的所有点的角度映射到一个(-π, π] 的区间
//         使所有向量都有序, 使用函数排序, 注意: 该函数需要先给 y 坐标再给 x 坐标
//      
//      3) 求直线: 这里使用点向式 p0 + vt, 用直线参数方程存储直线
//                点向式判断在左在右比较方便
//      
//      4) 求凸包时求的是点, 这道题求的是直线
//      5) 凸包会用栈底更新栈顶(闭包形式), 所以双端队列 维护两头, 都要更新
#include <iostream>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;
const int N = 510;
const double eps = 1e-8;

int cnt;        // 凸包数量
struct Line     // 直线{起点, 终点}
{
    PDD st, ed;
}line[N];
PDD pg[N], ans[N];  //pg[]:存储凸包的所有点, ans[]:表示答案
int q[N];

int sign(double x)      // 符号函数
{
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1; 
}

int dcmp(double x, double y)    // 比较函数
{
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

// 叉积
PDD operator-(PDD a, PDD b)
{
    return {a.x - b.x, a.y - b.y};
}

double cross(PDD a, PDD b)
{
    return a.x * b.y - a.y * b.x;
}

double area(PDD a, PDD b, PDD c)
{
    return cross(b - a, c - a);
}

// 求两条直线交点
// PDD{x,y}:存储的是直线的端点坐标
PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w)
{   
    auto u = p - q;     // 一个坐标的距离减去一个坐标的距离, 求出辅助线的距离
    double t = cross(w, u) / cross(v, w); // 因为相似, 所以可求出两个三角形的比值
    return {p.x + v.x * t, p.y + v.y * t}; // pv这条线段, 到焦点的距离就是 t 倍的 向量v
}

// 求半平面交两个直线的交点
PDD get_line_intersection(Line a, Line b)
{
    return get_line_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}

// 求角度
// ps: atan2 先算 y 轴再算 x 轴
double get_angle(const Line& a)
{
    return atan2(a.ed.y - a.st.y, a.ed.x - a.st.x);
}

// 排序的比较函数(按照向量的角度进行排序)
// !dcmp(A, B): 相等的情况
// 
// | /|
// |/ |
// a  b => 小于 0 是 a->b 顺时针方向转下来
bool cmp(const Line& a, const Line& b)
{
    double A = get_angle(a), B = get_angle(b);  // 两个有项直线的角度
    if (!dcmp(A, B)) return area(a.st, a.ed, b.ed) < 0; // 如果角度相等优先更靠左的排前面
    return A < B; 
}

// 这个函数很重要, 忘了画图
//
// bc 的交点是否子 a 的右侧
// bc 相当于求 line[q[i-1]] 和 line[q[i]] 的交点, 也就是判断 "次队尾" 和 当 "队尾" 的交点 
bool on_right(Line& a, Line& b, Line& c)
{
    auto o = get_line_intersection(b, c);       // 返回的是两线的交点
    
    //        ^      ^
    //    \   |     /
    //     \  |    /
    // _____\_|___/_____
    //       .| .        => 如果交点在 "新线段" 右侧, 就踢掉
    //
    // a.st 是原点(当前点)
    // "队尾" 和 "次队尾线段" 交点o 求出后, 判断的就是 "点o" 到 "a.st" 的距离 和 "a.ed" 到 "a.st" 的距离
    // 这两个向量的差积, 是否为负数, 负数就是顺指针也就是在右边     
    return sign(area(a.st, a.ed, o)) <= 0;      // 判断差积的面积是否为负, 为负数返回 true, 代表要删除
}

/*
        注意事项:
        当出现一个可以把队列里的点全部弹出去的向量（即所有队列里的点都在该向量的右侧），
        则我们 必须 先处理队尾, 再处理队首. 因此在循环中, 我们先枚举 --r; 的部分, 再枚举 ++l; 的部分, 才不会错.
*/

//  hh + 1: 队列始终保证两条边
// on_right(当前点, 次队尾, 队尾)
//      1) 先求出"次队尾"和"队尾"的交点 o
//      2) 判断 o 是否在 "当前点" 的右边, (当前点的向量顺指针能转到 o) 就是在右边 返回 true
double half_plane_intersection()
{
    sort(line, line + cnt, cmp);
    int hh = 0, tt = -1;
    for (int i = 0; i < cnt; ++ i )
    {
        // 如果两条线, 角度相同, 不用看
        if (i && !dcmp(get_angle(line[i]), get_angle(line[i - 1]))) continue;
        // 检查队尾直线和队尾前一条的交点是否在当前边的右边,  如果在右边则将元素踢出队列(角度相同的向量也踢出去) 
        // on_right 返回 true 代表队尾要踢出去
        while (hh + 1 <= tt && on_right(line[i], line[q[tt - 1]], line[q[tt]])) tt -- ;
        // 队头队尾都要判断, 队头就要反过来, 才能判断是否在右 
        while (hh + 1 <= tt && on_right(line[i], line[q[hh]], line[q[hh + 1]])) hh ++ ; 
        q[ ++ tt] = i;
    }
    // 队头更新队尾
    while (hh + 1 <= tt && on_right(line[q[hh]], line[q[tt - 1]], line[q[tt]])) tt -- ;
    // 队尾更新队头
    while (hh + 1 <= tt && on_right(line[q[tt]], line[q[hh]], line[q[hh + 1]])) hh ++ ;
    // 这样双端队列中存的就是半平面交的所有的直线
    
    // 最后求的是半平面交的轮廓面积
    // 求面积要先求轮廓线上的所有点, 先求出所有交点
    // 将队头重复一遍加队尾(闭包)
    // st .. elem .. elem .. ed .. st -> 也要求出 ed~st 的长度
    q[ ++ tt] = q[hh];  

    // 求一下轮廓线的所有交点
    // ans 从 0 开始记录答案
    int k = 0;
    for (int i = hh; i < tt; ++ i ) 
        ans[k ++ ] = get_line_intersection(line[q[i]], line[q[i + 1]]);

    // 求面积, 凸多边形 k 条边对应 k-2 个三角形, 所以要减 1 
    double res = 0;
    for (int i = 1; i + 1 < k; ++ i )
        res += area(ans[0], ans[i], ans[i + 1]);        // ans[0]:画完图就能发现求面积的的过程是从一个顶点连向所有点
    
    return res / 2; // 因为求的是两倍的三角形所以要除以 2
}

int main()
{
    // 第一行有一个整数 n, 表示凸多边形的个数, 以下依次描述各个多边形
    // 第 i 个多边形的第一行包含一个整数 mi, 表示多边形的边数, 以下 mi 行每行两个整数, 逆时针给出各个顶点的坐标
    int n, m; scanf("%d",&n);
    while (n -- )
    {
        scanf("%d", &m); // 每个凸多边形的变数
        for (int i = 0; i < m; ++ i ) scanf("%lf%lf", &pg[i].x, &pg[i].y);  // 凸多边形顶点的坐标
        for (int i = 0; i < m; ++ i ) // 将凸包的每条边存下
            line[cnt ++ ] = {pg[i], pg[(i + 1) % m]}; // pg[i]:存储的是端点的坐标    
    }
    double res = half_plane_intersection();
    printf("%.3lf\n", res);
    return 0;
}