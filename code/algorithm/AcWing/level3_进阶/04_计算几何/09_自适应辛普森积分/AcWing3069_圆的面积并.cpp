// 利用自适应辛普森积分, 求出当 x = x0 时, 与所有圆的交集的长度并f(x), 然后求长度并的积分即可
//
// 对于一条竖线来说其覆盖圆的长度是连续的, 其表示的函数连续, 可以用辛普森积分来处理, 其函数值 x 这条竖线跟圆的交集长度
// 另外, 有一个优化精度的方式, 即可能并不是所有的圆的位置都是连续的, 即可能在 x 方向上很多圆是一块一块放置的
// 不妨先将所有块预处理出来, 然后再对每一块执行自适应辛普森积分

#include <iostream>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

int n;
struct Circle
{
    PDD r;
    double R;
}c[N];

double asr(double l, double r, double s)
{
    auto mid = (l + r) / 2;
    
}

int main()
{   
    // 读入圆的数量, 读入圆心和半径
    scanf("%d", &n);        
    for (int i = 0; i < n; += i ) scanf("%lf%lf%lf", &c[i].r.x, &c[i].r.y, &c[i].R);
    double l = -2000, r = 2000;
    printf("%.3lf\n", asr(l, r, simpson(l, r)));
    return 0;
}