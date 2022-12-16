// 旋转卡壳是一种思想并不是模板
// - 如果求的是平面最近点就是 "分治" 的问题
// - 如果求的是平面最远点就是 "计算几何" 的问题
// 
// 平面最远点对的两个点在凸包上
//
// 旋转卡壳: 
//      想象一对平行线, 转着圈去卡凸包, 必然可以把直径卡出来
//      因为平行线旋转角度无穷多种, 所以我们只能去枚举离散的值, 因此我们不去枚举两个直线间的距离
//      而是去枚举对踵点间的距离, 同样可以证明两个对踵点必然可以枚举到最大值(详细证明看图)
// 如何枚举对踵点: 
//      找对踵点发生变化的时刻即可     
// 对踵点什么时候发生变化:
//      当一条平行线和某条凸边形边重合的时候, 就是对踵点发生变化的时刻
//      找发生变化的时刻等价于对于每条边来说要找到最远的点
//      我们可以发现当我们逆时针方向枚举所有边的时候, 每条边对应的最远点一定是逆时针方向走的
//      这是一个单调的过程, 所以可以用双指针算法, 从前往后一次枚举每条边, 对应的点的话从当前位置顺次往后走
//      每次找最大值即可
#include <iostream>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
const int N = 500010;

int n; 
PII q[N];
int stk[N], top;    // 栈
bool used[N];       // 判断点是否被用过

// 叉积
PII operator- (PII a, PII b)    // 两维向量减法
{
    return {a.x - b.x, a.y - b.y};
}

int operator* (PII a, PII b)    // 向量叉乘
{
    return a.x * b.y - a.y * b.x;
}

int area(PII a, PII b, PII c)   // 两个向量平行四边形面积(向量减法后叉积)
{
    return (b - a) * (c - a);
}

int get_dist(PII a, PII b)  // 距离
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// 旋转卡壳求凸包尽可能逆时针方向存
// 这个栈下标从 0 开始, 是左闭右开
void andrew()
{
    sort(q, q + n);
    for (int i = 0; i < n; ++ i )   // 求下凸壳
    {
        // 如果 "当前点" 在 栈中 最后两点形成的直线 的右边/下边, 就不断弹出  
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0)
        {
            // 不共线直接删除
            if (area(q[stk[top - 2]], q[stk[top - 1]], q[i]) < 0)
                used[stk[ -- top]] = false;
            else 
                top -- ;
        }   
        stk[top ++ ] = i;
        used[i] = true;
    }

    used[0] = false;  // 形成闭包

    for (int i = n - 1; i >= 0; i -- )  // 求上凸壳
    {
        if (used[i]) continue;
        while (top >= 2 && area(q[stk[top - 2]], q[stk[top - 1]], q[i]) <= 0)
            top -- ;
        stk[top ++ ] = i;
    }
    top -- ;        // 因为 0 好号点被插入 2 次
}

int rotating_calipers()
{
    if (top <= 2) return get_dist(q[0], q[n - 1]);
    int res = 0;
    
    // 枚举所有对踵点(要找的是平行线之间距离差最大的值, 只有当平行线和边重合时, 对踵点才会发生变化)
    // 所以我们枚举的就是对踵点之间的距离
    // 
    // i 和 i+1 是边, j 是顶点(j 从 2开始, 前两点枚举了)
    // 枚举这条边的两端哪一端和 j 的距离相差更大(叉积, 面积越大距离也越大)
    for (int i = 0, j = 2; i < top; ++ i )           
    {
        PII d = q[stk[i]], e = q[stk[i + 1]];   // 栈是左闭右开的区间但是每次取 2 个值

        // 循环更新是因为 j 一直在刷新, 因为每条边边和点的关系是, 先增加在再减小
        // 所以枚举到前一条边小于后一条边就结束
        while (area(d, e, q[stk[j]]) < area(d, e, q[stk[j + 1]])) 
            j = (j + 1) % top;    // 一共有 top 个点, j < top, (j + 1) <= top
        
        // 更新距离(while 循环出去后, 剩下的一定是比较远的顶点了, 判断两端端点距离 j 哪条更远)
        res = max(res, max(get_dist(d, q[stk[j]]), get_dist(e, q[stk[j]]))); 
    }
    return res;
}

int main()
{
    // 第一行包含一个整数 N
    // 接下来 N 行, 每行包含两个整数 x,y, 表示一个点的位置坐标
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i ) scanf("%d%d", &q[i].x, &q[i].y);
    andrew();
    printf("%d", rotating_calipers());       // 求一下凸包
    return 0;
}