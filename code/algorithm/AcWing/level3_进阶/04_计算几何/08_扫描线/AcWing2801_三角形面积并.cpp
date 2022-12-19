#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;
const int N = 110;
const double eps = 1e-8, INF = 1e6;

int n;          // 三角形的数量
PDD tr[N][3];   // 存储三角形的顶点
PDD q[N];       // 存储待合并的区间

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

PDD operator* (PDD a, double t)
{
    return {a.x * t, a.y * t};
}

double operator* (PDD a, PDD b)
{
    return a.x * b.y - a.y * b.x;
}

double operator& (PDD a, PDD b)
{
    return a.x * b.x + a.y * b.y;
}

// 判断是否在线段上(需要点积)
bool on_segment(PDD p, PDD a, PDD b)
{
    return sign((p - a) & (p - b)) <= 0;
}

// 如果在线段上就返回 INF, 如果不在就返回 o (需要叉积)
PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w)
{
    if (!sign(v * w)) return {INF, INF};
    auto u = p - q;
    auto t = w * u / (v * w);
    auto o = p + v * t;
    if (!on_segment(o, p, p + v) || !on_segment(o, q, q + w))
        return {INF, INF};
    return o;
}

// 求每条直线之间的并集的长度
double line_area(double a, int side)
{
    int cnt = 0;        // x = a, 上线段的个数
    
    // 和 a(横坐标) 这条线有交集的所有三角形
    for (int i = 0; i < n; ++ i )
    {
        auto t = tr[i];     // 表示当前三角形
        
        // 最小值如果严格大于 a(那段区间在 a 后面), 最大值如果严格小于 a(那段区间在 a 前面), 一定没有交点, 直接 continue
        // t[0] > a, t[2] < 0
        if (dcmp(t[0].x, a) > 0 || dcmp(t[2].x, a) < 0) continue;

        // 0 号位置和 1 号位置都在同一边上
        // t[0].x == a && t[1].x == a, 两个点都同一条边上(x 一样)
        if (!dcmp(t[0].x, a) && !dcmp(t[1].x, a))
        {
            // 两点完全在左侧, 两点的 x 轴有了, 将两点的 y 轴 记录进待合并区间
            // 此时 y 轴间存的关系其实是不确定的, 为了合并, 之后还要进行排序
            if (!side) q[cnt ++ ] = {t[0].y, t[1].y};
        }
        else if (!dcmp(t[2].x, a) && !dcmp(t[1].x, a))
        {
            // 两点完全在右侧, 记录其两点的 y 轴 记录进待合并区间
            if (side) q[cnt ++ ] = {t[2].y, t[1].y};
        }
        else
        {
            // 特殊情况判断完后, 判断剩下的情况, 可能三个交点, 也可能两个交点
            // 三个交点是因为: 三角形有个顶点在 x=a 上
            // 枚举 "第 i 个三角形" 和 "i+1 三角形" 是否有相交的点
            double d[3];
            int u = 0;
            // 枚举两个三角形的三个点(在 a 这个横坐标上枚举), 判断他们是否存在交点
            for (int j = 0; j < 3; j ++ )
            {
                // x=a 这条直线的两个端点(a, -INF), (a, +INF)
                // 因此点向式为: 
                //      - (a, -INF):竖直线段下面的点, (0, INF * 2):竖直线段的上面的点
                // t[j], t[(j + 1) % 3] - t[j]: 获得某条线段
                //     {a, -INF}, {0, INF * 2}: 竖直线段
                //     {a, -INF}: 从 x 轴指向负无穷
                //  {0, INF * 2}: 向量长度
                // 求出三角形其中一条边形成的向量 和 a(轴) 形成的向量的交点(说明梯形的某一部分是在这个段竖线内的)
                auto o = get_line_intersection(t[j], t[(j + 1) % 3] - t[j], {a, -INF}, {0, INF * 2});
                
                // 如果交点不是正无穷, 说明是有交点的
                // 将 y 坐标存下, 这个 y 坐标是对于 三角形的其中一边卡住了当前竖线的 x 轴(a) 
                if (dcmp(o.x, INF))
                    d[u ++ ] = o.y;
            }
            if (u)
            {   
                // 如果有交点, 将所有交点排序, 排的是 y 轴
                // q:所形成的交点的 y 轴
                // 排序为了方便将 y 轴合并
                // q 里面存的是一对一对 y 轴上的两端点
                sort(d, d + u);
                q[cnt ++ ] = {d[0], d[u - 1]};
            }
        }
    }
    if (!cnt) return 0;

    // 上下两端点, 需要保证每个区间左端点小于右端点
    // 将较大的换到后面
    for (int i = 0; i < cnt; i ++ )
        if (q[i].x > q[i].y)
            swap(q[i].x, q[i].y);

    // 区间合并求区间长度
    sort(q, q + cnt);
    double res = 0, st = q[0].x, ed = q[0].y;
    for (int i = 1; i < cnt; i ++ )
        if (q[i].x <= ed)                   // 如果 "新区间" 的开头 比 "ed" 小(被 ed 的包裹住了就进行尝试更新下新 ed)
            ed = max(ed, q[i].y);
        else
        {   
            // 新区间的开头更大, 就结算 "旧区间", 并再更新一段区间
            res += ed - st;
            st = q[i].x, ed = q[i].y;
        }
    res += ed - st;

    // 返回结果
    return res;
}

// a: 交点的横坐标, b: 交点的横坐标, 就相当于左右的竖线, 求出竖线之间的梯形
double range_area(double a, double b)
{
    // 0: 表示左边, 1: 表示右边
    // (底边 + 顶边) * 高 / 2
    // 算出两线之间横坐标的面积
    // line_area(a, 0):求出底边这个集合
    // line_area(b, 1):求出顶边这个集合
    return (line_area(a, 0) + line_area(b, 1)) * (b - a) / 2;
}

int main()
{
    // 第一行为 n, 即三角形的个数
    // 以下 n 行, 每行 6 个实数 x1,y1,x2,y2,x3,y3, 代表三角形的顶点坐标
    // 坐标均为不超过 10^6 的实数, 输入数据保留 1 位小数
    scanf("%d", &n);
    
    vector<double> xs;     // 存储顶点和交点的横坐标

    for (int i = 0; i < n; i ++ )
    {
        for (int j = 0; j < 3; j ++ )
        {
            scanf("%lf%lf", &tr[i][j].x, &tr[i][j].y);      // 输入三角形的三个坐标
            xs.push_back(tr[i][j].x);   // 插入三角形的横坐标
        }
        // 给三角形的三个点排序, 按照横坐标排序, 保留第一个点横坐标最小, 最后一个点横坐标最大
        // 为了方便在 line_area 中判断三角形和扫描线划分的区间是否有交集
        sort(tr[i], tr[i] + 3);
    }

    // 求三角形之间的交点
    // 因为是第 i 个三角形和第 j 个三角形找交点, 第 i 个三角形和 [i+1, n) 区间的三角形对比完后
    // 区间中的三角形都和该 三角形i对 比过了, 所以是保序的
    for (int i = 0; i < n; i ++ )
        for (int j = i + 1; j < n; j ++ )
            for (int x = 0; x < 3; x ++ )
                for (int y = 0; y < 3; y ++ )
                {
                    // 求出 三角形i 和 三角形j 三条边中的各个交点
                    // 
                    // start: tr[i][x]
                    // tr[i][(x + 1) % 3] - tr[i][x]: tr[i][x] 的向量, 三角形的其中一条边 
                    auto o = get_line_intersection(tr[i][x], tr[i][(x + 1) % 3] - tr[i][x],
                                                    tr[j][y], tr[j][(y + 1) % 3] - tr[j][y]);
                    if (dcmp(o.x, INF))
                        xs.push_back(o.x);
                }
    
    sort(xs.begin(), xs.end());

    //    xs:存储顶点和交点的横坐标
    // xs[i]:交点的横坐标
    double res = 0;
    for (int i = 0; i + 1 < xs.size(); i ++ )
        if (dcmp(xs[i], xs[i + 1]))
            res += range_area(xs[i], xs[i + 1]);    // xs[i] 和 xs[i + 1] 之间的面积
    
    printf("%.2lf\n", res);
    return 0;
}