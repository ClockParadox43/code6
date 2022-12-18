// q:给定 n 个矩形, 用来求面积并
// 作用: 扫描线用来求面积和周长
// 思路: 我们直接求所有矩形落在竖方向长条内的区间，将所有区间找出来后做一个区间合并
//       所有区间合并完的长度和就是阴影部分的高的和 =>  底 x 高 = 面积
//
// 区间和并和辛普森积分都是用来求并集的面积
//
// 使用扫描线的条件: 每一个长条内的区域比较容易求才可以
// 
// 时间复杂度:(n^2)logn 
//           最坏情况一共有 O(n) 个区间, 每个长条内都有 n 个小线段, 排序(nlogn)
//           合并 n 个线段是 n, 所以是 (n^2)logn 
#include <iostream>
#include <algorithm>
#include <vector>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int N = 1010;

int n;
PII l[N], r[N];     // 定义矩形的左上角和右下角 
PII q[N];

// 用 a 和 b 表示长条的左右坐标
// a(x) -> b(x) 的长条内一定不会出现中间位置
// 矩形和长条的关系 要么完全没有交集, 要么横跨整个长条
// 所有交集的宽度是相同的
LL range_area(int a, int b)
{
    int cnt = 0;
    // 遍历所有矩形, 将所有矩形和长条的交集完全存下来
    // 所有矩形被长条分割后 底边 完全相同, 所以只需要存 高 的区间
    for (int i = 0; i < n; i ++ )
        if (l[i].x <= a && r[i].x >= b)     // 如果有交集就存: 矩形的上边界和下边界
            q[cnt ++ ] = {l[i].y, r[i].y};  // 矩形的左上角右上角 的 上边界和下边界
    
    if (!cnt) return 0;
    
    // 排序  
    sort(q, q + cnt);
    
    LL res = 0;
    
    // 一个矩形的 st:左上角的 y
    //           ed:右下角的 y
    int st = q[0].x, ed = q[0].y;

    // 进行区间和并
    for (int i = 1; i < cnt; i ++ )
        if (q[i].x <= ed)         // 新的左上角的 y <= 旧的右下角的 ed
            ed = max(ed, q[i].y); // 旧的右下角的 ed 和 新的右下角的 ed 求 max, 所有 y 轴更新成更高的 y 轴
        else
        {
            res += ed - st;     // 将竖线的矩形的所有高累加
            st = q[i].x, ed = q[i].y;   // 更新成为新的 左上角和右下角的 y 轴
        }
        
    res += ed - st;     // 求出所有高
    return res * (b - a);       // 底 * 高
}

int main()
{
    // 第一行包含整数 n
    // 接下来 n 行, 每行包含四个整数 x1,y1,x2,y2, 表示其中一个矩形的左下角坐标 (x1,y1) 和右上角坐标 (x2,y2)
    // 注意, 坐标轴 x 轴从左向右延伸, y 轴从下向上延伸
    scanf("%d", &n);
    
    vector<int> xs;     // 方便离散化, 将所有出现过的横坐标存入
    for (int i = 0; i < n; ++ i ) 
    {
        scanf("%d%d%d%d", &l[i].x, &l[i].y, &r[i].x, &r[i].y);
        xs.push_back(l[i].x), xs.push_back(r[i].x);
    }
    sort(xs.begin(), xs.end());

    LL res = 0;
    for (int i = 0; i + 1 < xs.size(); ++ i )
        if (xs[i] != xs[i + 1])                     // xs[i]:左上角的横坐标, xs[i + 1]:右上角的横坐标, x 轴重复说明这是一条线没有面积
            res += range_area(xs[i], xs[i + 1]);    // 如果 x 轴能形成面积面积, 那么数轴中的举证的底 都一样, 就去求
    
    printf("%lld\n", res);
    
    return 0;
}