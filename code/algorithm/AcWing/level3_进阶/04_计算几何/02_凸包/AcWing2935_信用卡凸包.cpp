// 切线性质: 切线和圆只有一个公共点
//          切线和圆心的距离等于圆的半径
//          切线垂直于经过切点的半径
// 
// 只要把信用卡的四个角的位置求出来, 并且对这 4n 个点做一遍凸包, 并且加上圆周长即可
// 但是怎么求这四个点呢 ?
// 显然可以先把它平移到原点, 然后在原点进行旋转, 再平移回去

#include <iostream>
#include <algorithm>
#include <cmath>

#define x first
#define y second    

using namespace std;

typedef pair<double, double> PDD; // 存坐标
const int N = 40010;    // 4 个角开 4 倍
const double pi = acos(-1);

int n, cnt;
PDD q[N];
int stk[N], top;        
bool used[N];

// 旋转公式: 将 a 旋转 b
PDD rotate(PDD a, double b)
{
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}

// 求叉积
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

// 求距离
double get_dist(PDD a, PDD b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double andrew()
{
    sort(q, q + cnt);
    for (int i = 0; i < cnt; ++ i )
    {
        // 如果新点在次栈顶元素右边, 也就是面积小于等于 0, 弹出次栈顶元素
        // 直到新点在次栈顶元素左边
        while (top >= 2 && area(q[stk[top - 1]], q[stk[top]], q[i]) <= 0)
        {
            if (area(q[stk[top - 1]], q[stk[top]], q[i]) < 0)     
                used[stk[top -- ]] = false;
            else top -- ;  // 因为求的是下凸壳, 所以如果共线就标记后删除
        }
        stk[ ++ top] = i;
        used[i] = true;
    }
    used[0] = false;
    for (int i = cnt - 1; i >= 0; -- i )
    {
        if (used[i]) continue;
        while (top >= 2 && area(q[stk[top - 1]], q[stk[top]], q[i]) <= 0)
            -- top;
        stk[ ++ top] = i;
    }

    double res = 0;
    for (int i = 2; i <= top; ++ i )        // 和从 0 开始等价(那牛那道题)
        res += get_dist(q[stk[i - 1]], q[stk[i]]);
    return res; 
}
int main()
{
    // 第一行是一个正整数 n, 表示信用卡的张数
    // 第二行包含三个实数 a,b,r, 分别表示信用卡(圆滑处理前)竖直方向的长度、水平方向的长度, 以及 1/4 圆的半径
    // 之后 n 行，每行包含三个实数 x,y,θ, 分别表示一张信用卡中心(即对角线交点) 的横、纵坐标，以及绕中心逆时针旋转的弧度
    scanf("%d", &n);
    double a, b, r; 
    scanf("%lf%lf%lf", &a, &b, &r);
    a = a / 2 - r, b = b / 2 - r;               // 先将长度除以 2 再减去一个 r, 作为旋转时候的偏移量

    // 3 _____0
    //  |____|
    // 2     1 
    int dx[] = {1, 1, -1, -1}, dy[] = {1, -1, -1, 1};       // 逆时针转过去
    while (n -- )
    {
        double _x, _y, z; 
        scanf("%lf%lf%lf", &_x, &_y, &z); // 卡的横纵坐标以及旋转互弧度
        // 枚举 4 个方向的角
        for (int i = 0; i < 4; ++ i )
        {
            auto t = rotate({dx[i] * b, dy[i] * a}, -z);  // 得到旋转后的点, 因为旋转的角度为逆时针, 但是旋转函数是顺时针, 所以 角度z 取反
            q[cnt ++ ] = {_x + t.x, _y + t.y};          // 旋转完后将起点平移到中心的位置
        }
    }

    double res = andrew();
    printf("%.2lf", res + 2 * pi * r);  // 凸包周长 + 圆周长
    return 0;
}