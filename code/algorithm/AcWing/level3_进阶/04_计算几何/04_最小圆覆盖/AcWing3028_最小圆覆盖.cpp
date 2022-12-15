// 性质1: 最小圆是唯一性
// 性质2: 若点 p 不在 S 的最小覆盖圆内部, 则 p 必在 {p}∪S 的最小覆盖圆的边上 
//
// 1) 将所有点集随机化(该算法建立在完全随机的基础之上), 
// 2) 从前往后枚举每一个点(从第 2 个点开始枚举), 假设已经求出 1~i-1 的最小覆盖圆
//
//          枚举 3 个点, 3 个点可以确定一个圆
//          for(int i = 2; i <= n; ++ i )
//              if(在) 继续枚举
//              if (i 不再最小覆盖圆内, 那就在圆边上)
//                   
//      - 初始化: 将 1 号点放在圆里即可(包含一个点的最小覆盖圆就是这个点)
//      - 从前往后递推
//      - 假设已经求出 1~i-1, 这 i-1 个点的最小覆盖圆的话, 需要将第 i 个点加入集合 
//          情况1: 第 i 个点已经在集合里了, 继续枚举
//          情况2: 如果第 i 个点不在最小覆盖圆的内部, 根据性质2, 那么 i 一定在 1~i 的最小覆盖圆的边上
//
//      - 假设此时已经确定出, 1~i 的最小覆盖圆边上的 1 个点, 我们要求的是第 i 个点的最小覆盖圆
//        因此我们还需要确定出第 2 个点和第 3 个点
//              - 因此枚举所有能够覆盖 1~i 的并且 i 在圆边上的所有的圆, 找出最小圆     
//                只枚举 i 在圆边上的所有的圆(因为最优解一定在圆边上, 所以我们只要考虑 i 在圆边上的圆)
//                如何枚举 ?
//                     - 因为要枚举所有 i 在圆边上的圆, 所以我们从最小的圆开始枚举(即包含 i 这一个点的圆) 
//                       也就是将覆盖圆变成 i 这一个点, 此时圆心就是 pᵢ. 然后我们进行下一重循环, 目的为了找第 2 个点
//                            - 假设已经求出能够覆盖 1~j 和 i, 并且 i 在圆边上所有圆中半径最小的圆
//                                for(int j = 1; j < i; ++ j) (找第 2 个点: 枚举 1~j-1 个点且第 i 个点在圆边上)
//                                - 要将点 j 加入到这个集合中                               
//                                   情况1: 如果点 j 在符合条件的圆中, 继续枚举下一个 j             
//                                   情况2: j 不在圆内, 则 j 必在能够覆盖 1~j 和 i, 且 i 在圆边上的最小覆盖圆边上
//                                          ps: 1~i-1 在第 1 层循环的最小覆盖圆中, 记作 S1, i 在 S1 边上
//                                              1~j-1 在第 2 层循环的最小覆盖圆中, 记作 S2, i 在 S2 边上, j 在 S2 边上(对应情况 2)
//                                              枚举的是 i 在 S1 边上的所有圆 S2, j 在 S2 边上, i 也在 S2 边上 
//                                              也就是 i 在 S1 边上, 也在 S2 边上, S2 可以覆盖 i-1 和 j-1 的所有点
//                                   这相当于在 性质1和2上又添加了限制, 这种情况下, 性质1 和 2 依旧满足, 详细见证明
//                                   问题1: i 的这个条件是否可以不用加 ?
//                                          - 因为我们需要 3 点确定一个圆, 最优解又在圆边上
//                                            如果不加这个 "且 i 在圆S1 边上的最小覆盖圆 S2 边上" 的限制条件
//                                            那么 i 是否在 S2 边上这是不一定成立的, 所以必须把限制加到条件中
//                                            详细见证明
//                            - 最后将以 i 为直径的圆赋值给答案
// 
//  - 至此我们已经确定了 2 个点, 假设已经枚举出能够覆盖 1~k-1 且 i,j 必然在圆上
//        for(int k = 1; k < j; ++ k ) 
//            - 情况 1: k 在圆里, 继续枚举
//            - 情况 2: k 不在圆里, 那么 k 一定在圆边上 (能够覆盖 1~k-1, 且在i, j 都在圆边上的最小圆的边上)
//                      因此枚举能够覆盖 1~k-1 且 i,j,k 都在圆边上的所有圆
//     证明过程和第二层循环差不多
//     - 当 k 确定后, 那么 i, j, k 就可以组成一个圆, 也就没有下一重循环(最多 3 层循环)
//
// 求出 AB 的中垂线, 求出 AC 的中垂线, 他们的交点就是圆心
// 圆心和任意一点的距离就是半径
// 方向: 向量 AB 顺时针旋转 90° 得到中垂线的方向
// 起点: 起点也就是中垂线的中点, AB的坐标 / 2 

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;
const int N = 100010;
const double eps = 1e-12;
const double PI = acos(-1);     // 需要旋转 90°

int n;
PDD q[N];       // 存储点
struct Circle   // 存储圆
{
    PDD p;
    double r;
};

int sign(double x)     // 符号函数
{
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

int dcmp(double x, double y)    // 高精度比较函数
{
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}   

PDD operator- (PDD a, PDD b)        // 向量减法
{
    return {a.x - b.x, a.y - b.y};
}

PDD operator+ (PDD a, PDD b)        // 向量加法
{
    return {a.x + b.x, a.y + b.y};
}

PDD operator* (PDD a, double t)     // 向量数乘
{
    return {a.x * t, a.y * t};
}

double operator* (PDD a, PDD b)     // cross() 向量叉乘, 注意这里返回的不是坐标是数值
{
    return a.x * b.y - a.y * b.x;
}

PDD operator/ (PDD a, double t)     // 求中垂线用的数除
{
    return {a.x / t, a.y / t};
}

PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w)   // 求交点
{
    auto u = p - q;
    double t = w * u / (v * w);     // 因为上面的重载, 我们得到的是叉积 cross()
    return p + v * t; 
}

PDD rotate(PDD a, double b)        // a 旋转至 b
{
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}

// (a + b) / 2: 为 x 轴, a+b: a~b 的长度, /2 求出终点
// rotate(b - a, PI / 2): y 轴, b-a 算出 a 到 b 的距离, 再旋转 PI/2°(90°)
// 
// B \  /      / C
//    \/      /        中垂线: AB, AC 取中点旋转 90°
//    /\     /      
//      \ A /
pair<PDD, PDD> get_line(PDD a, PDD b)       // 求中垂线
{
    return {(a + b) / 2, rotate(b - a, PI / 2)};    // 中点, 顺时针旋转 90°, a 是原点
}

double get_dist(PDD a, PDD b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

Circle get_circle(PDD a, PDD b, PDD c)  // 求出 3 个点的外接圆
{
    auto u = get_line(a, b), v = get_line(a, c);       // pair<PDD, PDD} u(A->B), v(A->C): 两个向量的坐标
    auto p = get_line_intersection(u.x, u.y, v.x, v.y);// PDD p: 交点的坐标, 得到交点, AB, AC 的交点

    //   . p
    //   | 
    //   | 
    //   a
    return {p, get_dist(p, a)};      // 返回 {交点的坐标, 和交点到 a 的距离, 也就是半径}
}

int main()
{
    // 第一行包含一个整数 N
    // 接下来 N 行, 每行包含两个实数, 表示一个点的坐标 (Xi, Yi)
    scanf("%d", &n);      
    for (int i = 0; i < n; i ++ ) scanf("%lf%lf", &q[i].x, &q[i].y);
    random_shuffle(q, q + n);     // 无序

    Circle c({q[0], 0});    // 起始圆: 0 号点的坐标, 半径 0 
    for (int i = 1; i < n; ++ i )   // 从第 2 个点开始枚举
    {
        // 如何判断一个点是否在圆内 ? 
        //      - 判断点到圆心的距离是否小于半径

        if (dcmp(c.r, get_dist(c.p, q[i])) < 0) // 说明 q[i] 在当前圆外
        {
            c = {q[i], 0};  // c 更新成圆外的点, 更新 c 是为了记录点是否在圆内
            
            // 枚举这个圆上的下一个点
            for (int j = 0; j < i; ++ j )   
                if (dcmp(c.r, get_dist(c.p, q[j])) < 0) // 说明 q[j]在当前圆外, p[j] 必然在满足条件的圆的边上 
                {
                    // 以q[i]、q[j]为直径的圆, q[i], q[j] 的中点(得到的是坐标), 半径的 q[i]~q[i] 的距离 / 2
                    c = {(q[i] + q[j]) / 2, get_dist(q[i], q[j]) / 2};
                    
                    // 枚举第 3 个点
                    for (int k = 0; k < j; ++ k )
                        if (dcmp(c.r, get_dist(c.p, q[k])) < 0) // q[k] 不在圆的边上, 那么这个圆就有了
                            c = get_circle(q[i], q[j], q[k]);   
                }
        }
    }
    printf("%.10lf\n", c.r);
    printf("%.10lf %.10lf\n", c.p.x, c.p.y);
    return 0;
}