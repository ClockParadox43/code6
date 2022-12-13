// Andrew算法:
// 时间复杂度O(nlogn) - 时间主要是在对坐标的快排上
// Andrew算法是对Graham扫描法的改进
// 
// 原理：
//  利用夹角, 让整个图形保持左转, 先将最左边的前两个点加入栈中, 每次加入新点时判断是否左拐(叉积大于0), 
//  如果是就将新点直接加入, 如果不是, 就弹出栈顶, 直到左拐, 将新点加入栈中
//  ps:栈中要保证至少有一个元素, 也就是 top>=2 的时候才可以弹出栈顶
// 第一遍找的都是 y 小的点, 也就是下凸包, 上面没有, 然后我们反着再来一遍。
// 
// 流程:
//  1.将所有点进行快排, 以 x 为第一关键字, y 为第二关键字升序排序
//  2.先从左至右维护凸包的下半部分, 然后再从右至左维护上半部分
//  3.将第一个点放入栈中 (这个点一定时凸包的最左边的点了, 是不会清理掉的), 然后在将第二个点放入栈中. 当栈中元素大于等于 2 的时候, 就要判断栈顶元素是否还要保留
//      如果 "新栈顶元素" 在 "次栈顶元素" 延长的直线 "左边", 那么, 直接将新点加入栈中
//      如果 "新栈顶元素" 在 "次栈顶元素" 延长的直线 "右边", 那么, 将栈顶元素不断弹出, 直到 "新栈顶元素" 在 "次栈顶元素" 延长的直线 "左边" 结束
//  4.将最左侧的点标记为可用(为了保证闭合), 重复 步骤 2 和 3.
//  5.堆中所有点就是构成凸包的所有点
//
// 那么, 我们这个过程, 是从左往右走的, 而且每次找的点都是在当前直线的右侧, 也就是直线的下方向, 那么我们得到的凸包就是我们的下半部分
// 求上半部分的时候，从右往左排就自然而然是对的了

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define x first
#define y second
using namespace std;

typedef pair<double, double> PDD;
const int N = 10010;

int n;
PDD p[N];
int stk[N], top;
bool used[N];
// used数组 表示这个点是否已经在底边上了, 如果在了, 就不用考虑底边上的边了
// 注意在我们求 "上凸包" 的时候, 要把 used[0] 置为 false
// 因为我们求的闭包长度 (首是 0 末是 0 闭环)

//重载减和乘  叉积
PDD operator-(PDD a,PDD b)
{
    return {a.x - b.x,a.y - b.y};
}

double operator*(PDD a,PDD b)
{
    return a.x * b.y - a.y * b.x;
}

//判断顺时针还是逆时针 有向面积
double area(PDD a, PDD b, PDD c) 
{
    return (b - a) * (c - a);
}

double dis(PDD a, PDD b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double andrew()
{
    // pair 默认对 x 升序, 当 x 相同时对 y 升序
    sort(p, p + n);
    int top = 0;
    for (int i = 0; i < n; ++ i )
    {
        // 如果 "次栈顶元素" 延长的直线 "顺时针" 可以转到 "新栈顶元素" (顺时针的求叉乘为负数)
        // 那么, 将栈顶元素不断弹出, "次栈顶元素" 延长的直线 "逆时针" 可以转到 "新栈顶元素" 结束
        while (top >= 2 && area(p[stk[top - 1]], p[stk[top]], p[i]) <= 0)
        {
            // 不共线直接删掉
            if (area(p[stk[top - 1]], p[stk[top]], p[i]) < 0)
                used[stk[top -- ]] = false;
            else 
                top -- ;        // 共线删除, 但不要置 false 因为在下凸壳上, 如果变成 false, 求上凸壳还会入栈
        }
        stk[ ++ top] = i;       // 加入当前栈
        used[i] = true;         // 置 true
    }
    used[0] = false;
    for (int i = n - 1; i >= 0; -- i )
    {
        if (used[i]) continue;
        while (top >= 2 && area(p[stk[top - 1]], p[stk[top]], p[i]) <= 0)
            top -- ;
        stk[ ++ top] = i;
    }
    
    double res = 0;
    for (int i = 0; i < top; i++ )      // 累加上栈中点的距离
        res += dis(p[stk[i]], p[stk[i + 1]]);

    return res;
}

int main()
{
    // 第一行包含整数 N, 表示奶牛们喜爱的地点数目
    // 接下来 N 行, 每行包含两个实数 Xi, Yi, 表示一个地点的具体坐标
    // 本题不共线, 求周长时会多累加
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i ) scanf("%lf%lf", &p[i].x, &p[i].y);
    
    double res = andrew();
    printf("%.2lf\n", res);

    return 0;
}

