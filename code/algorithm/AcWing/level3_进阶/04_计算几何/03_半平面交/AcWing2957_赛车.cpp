// 赛道无限长, 赛车速度不一样, 赛车速度是恒定的, 输出所有排到过第一名的赛车
// sᵢ = kᵢ + vᵢ * t (速度 * 时间 = 路程), kᵢ:起点, t ≥ 0
// 
//
// 步骤:
//  加两条额外的直线(S, t), 将考虑的范围限制在第一象限内
//  先得到所有直线, 看下那条直线是在半平面交上的, 哪些直线在半平面交上, 哪些赛车就可能领先
// 
// 边界:
//  1) 有的赛车直线完全一样, 如果有完全平行的直线, 求交点不容易求 (直接求会漏掉赛车)
//      - 可以让每种直线对应一堆赛车, 对这些直线判重, 将每种直线对应到一堆赛车列表上
//        这样处理的时候就不会有完全相同的直线了
//
//  2) 如果有多个直线共享一个点
//      - 那么这多个直线都要存下来
//        所以 on_right函数当等于 0 时, 占某端直线的两个交点, 在当前向量线上的话, 也要留下
//        只有完全在右侧才应该删掉 
//
//  最后看下轮廓线上有哪些直线即可
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

#define x first
#define y second
using namespace std;

typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LD, LD> PLD;
const int N = 10010;
const LD eps = 1e-18;           // 精度试出来的(数据范围 10^9, 那么它的叉积就是 10^18 级别)

int n, cnt;     // n: n 个赛车, cnt: 真实的线的数量
struct Line
{
    PLD st, ed;
    vector<int> ids;        // 车编号
}line[N];
int ki[N], vi[N];
int q[N], ans[N];

int sign(LD x)
{
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

int dcmp(LD x, LD y)    // 比较函数
{
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

// 叉积
PLD operator-(PLD a, PLD b) { return {a.x - b.x, a.y - b.y}; }
LD cross(PLD a, PLD b) { return a.x * b.y - a.y * b.x; }
LD area(PLD a, PLD b, PLD c)
{
    return cross(b - a, c - a);
}

// 求角度函数 ps: atan2 先算 y 轴再算 x 轴
LD get_angle(const Line& a)
{
    return atan2(a.ed.y - a.st.y, a.ed.x - a.st.x);
}

// 排序的比较函数(按照向量的角度进行排序)
bool cmp(const Line& a, const Line& b)
{
    LD A = get_angle(a), B = get_angle(b);
    if (!dcmp(A, B)) return area(a.st, a.ed, b.ed) < 0;
    return A < B;
}
// 求两条直线交点
// PLD{x,y}:存储的是直线的端点坐标
PLD get_line_intersection(PLD p, PLD v, PLD q, PLD w)
{
    auto u = p - q;   // 一个坐标的距离减去一个坐标的距离, 求出辅助线
    LD t = cross(w, u) / cross(v, w);       // 因为三角形相似, 所以求出两个三角形的面积比
    return {p.x + v.x * t, p.y + v.y * t};  // pv这条线段, 到焦点的距离就是 t 倍的 向量v
}

PLD get_line_intersection(Line& a, Line& b)
{
    return get_line_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}

// 判断 bc 的交点是否在 a 的右侧
bool on_right(Line& a, Line& b, Line& c)
{
    auto o = get_line_intersection(b, c);
    return area(a.st, a.ed, o) < 0;
}

void half_plane_intersection()
{
    sort(line, line + cnt, cmp);
    int hh = 0, tt = -1;
    for (int i = 0; i < cnt; ++ i )
    {
        // 如果两条线, 角度相同, 不用看
        if (i && !dcmp(get_angle(line[i - 1]), get_angle(line[i]))) continue;
        while (hh + 1 <= tt && on_right(line[i], line[q[tt - 1]], line[q[tt]])) tt -- ;
        while (hh + 1 <= tt && on_right(line[i], line[q[hh]], line[q[hh + 1]])) hh ++ ;
        q[ ++ tt] = i;
    }

    // 和上一题相比, 这题不需要求周长/面积, 所以不需要算 队尾到队头
    
    // 队头更新队尾
    while (hh + 1 <= tt && on_right(line[q[hh]], line[q[tt - 1]], line[q[tt]])) tt -- ;
    // 队尾更新队头
    while (hh + 1 <= tt && on_right(line[q[tt]], line[q[hh]], line[q[hh + 1]])) hh ++ ;

    int k = 0;
    for (int i = hh; i <= tt; i ++ )  // 枚举队列中的所有直线
        for (auto id: line[q[i]].ids) // 遍历第 i 个 line[] 中的 数组
            ans[k ++ ] = id;          // 将直线所在赛车编号存入 ans 数组
    sort(ans, ans + k);               // 题目要求升序返回

    printf("%d\n", k);
    for (int i = 0; i < k; i ++ ) printf("%d ", ans[i]);
    puts("");
}

int main()
{
    // 第一行有一个正整数 N 表示赛车的个数
    // 接下来一行给出 N 个整数, 按顺序给出 N 辆赛车的起始位置
    // 再接下来一行给出 N 个整数, 按顺序给出 N 辆赛车的恒定速度
    scanf("%d", &n);
    map<PII, vector<int>> ids;  // 判重数组, map 最好不要用 long double 会出现精度问题
    for (int i = 1; i <= n; ++ i ) scanf("%d", &ki[i]);     // 输入 n 辆赛车起始位置
    for (int i = 1; i <= n; ++ i ) scanf("%d", &vi[i]);      // 输入 n 辆赛车恒定速度
    
    // 将所有的 ki, vi 加入 ids 中
    for (int i = 1; i <= n; ++ i ) ids[{ki[i], vi[i]}].push_back(i);
    
    // 将所有直线加入到不同的集合中去, 将平面指标坐标系的 x 轴 y 轴加入到集合中去
    line[cnt ++ ] = {{0, 10000}, {0, 0}};       // y 轴 ps: 从上往下指
    line[cnt ++ ] = {{0, 0}, {10000, 0}};       // x 轴 
    
    // 将所有的直线加入line[]
    // [k, v] = {PII, v}
    // PII:{起始位置, 恒定速度} 
    //   v:第 i 辆赛车
    // 这里起点设置 (0,k), 终点横坐标设置成1, 纵坐标路程: sᵢ = kᵢ + vᵢ * t
    // k.x:起始位置, k.y:恒定速度
    for (auto& [k, v]: ids) 
        line[cnt ++ ] = {{0, k.x}, {1, k.x + k.y}, v}; // 随便找直线所在的两个点, 将所在点和赛车编号存入 line[]
    
    // 此时 line[] 中已经存储了每一辆车的编号, 和它的线段

    half_plane_intersection();
    return 0;
}




