// 辛普森积分作用: 本质用来求积分
// 辛普森积分的思路: 
//      - 求面积的和扫描线法很相似, 将图像分割成若干个长条
//        整个面积就是所有长条面积的和
// 和扫描线的不同点: 
//      - 辛普森积分用近似方法求, 而扫描线划分为长条后, 求的是精确值
//
// 将近似变成精确:
//      将划分的 δₓ 趋于 0 的时候(划分的非常细, 无限接近 0)该图形的面积, 就可以取这个近似面积的值
//      
// 自适应: 根据精度, 自适应去细分区间
//   作法: 
//      - 先用自适应近似求整个区间的值, 求抛物线面积, 等分成 2 部分, 每部分分别近似
//         | __|__ |
//         |/ L|R \|
//         S - (L + R) < eps
//        如果他们之间的误差小于一个 eps, 说明近似很准
//        如果误差很大, 用辛普森积分求左半部分/右半部分的面积
//      - 区间越小, 精度越大

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const double eps = 1e-12;

double f(double x)      // 自定义函数
{
    return sin(x) / x;
}

double simpson(double l, double r)      // 辛普森积分
{
    double mid = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;
}

double asr(double l, double r, double s)    // 递归做自适应
{
    // 将区间分成两部分, 一部分在左半边, 一部分在右半边
    double mid = (l + r) / 2;
    auto left = simpson(l, mid), right = simpson(mid, r);
    
    // 小于 eps 说明精度很小了, 返回 left + right
    if (fabs(left + right - s) < eps) return left + right;
    
    // 
    return asr(l, mid, left) + asr(mid, r, right);
}

int main()
{
    double a, b; scanf("%lf%lf", &a, &b);
    printf("%.6f\n", asr(a, b, simpson(a, b)));
    return 0;
}