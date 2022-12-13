#include <iostream>
#include <algorithm>
#include <cstring>

#define x first
#define y second
using namespace std;

typedef long long LL;
typedef pair<int, int> PLL;

const int N = 5010;

PLL a[N], b[N];     // a[]存隔板上的坐标, b[]存隔板下的坐标
int ans[N];         // ans[] 存每个区间的玩具数量
int n, m;

// 模板: a.x * b.x - a.y * b.y
LL cross(LL x1, LL y1, LL x2, LL y2)    // 求叉积
{
    return x1 * y2 - x2 * y1;
}

// a:隔板下坐标 -> a 是原点
// b:隔板上坐标
// c:玩具坐标
//    . |
LL area(PLL a, PLL b, PLL c)    // 求点是否在某个隔板的左侧, 如果子左侧 return > 0, 输出为正
{
    return cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);   // a 是原点
}

// (x1, y1):玩具的坐标
// area:注意这倒着存进去, a[]上, b[]下, b 是原点, 对应 area(原点, 端点, 端点)
//      如果是正数, 就表示 玩具在隔板左边, 那么 r 就找过来 
// 返回:玩具右边纸板的位置
int find(LL x1, LL y1)    // 找这个玩具在哪个隔板的左侧
{
    int l = 0, r = n;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (area(b[mid], a[mid], {x1, y1}) > 0) r = mid;        // b[mid],a[mid]: 隔板的上下端点, {x1, y1}: 要找的玩具
        else l = mid + 1;
    }
    return r;
}

int main()
{   
    // 输入: n 个纸板, m 个玩具, 收纳盒的左上角坐标为 (x1,y1), 右下角坐标为 (x2,y2)
    //      
    //      接下来 n 行, 每行包含两个整数 (uᵢ, lᵢ), 表示第 i 个纸板的两个端点坐标分别为  (uᵢ, y1) 和 (lᵢ, y2)
    //      数据保证纸板之间不相交, 且按照从左至右顺序依次给出
    //      
    //      接下来 m 行, 每行包含两个整数 (xᵢ, yᵢ), 表示第 j 个玩具的位置坐标, 数据保证玩具不会恰好落在纸板上, 也不会落在盒子外 
    //
    //
    // 整体思路: 枚举每个点在每个区域 
    //          每个玩具 都有对应, 出现在 右边所有向量的左侧, 同时是在左边所有向量的右侧 (可以用二分)
    //          用叉积可以快速判断在左侧还是右侧 (左侧为正, 右侧为负)
    //  
    bool is_first = true;      // 判断是否需要输出一行 (题目限制最后一组数据不能输出空行)
    while (cin >> n, n)     
    {
        LL x1, y1, x2, y2;    // (x1,y1)为整个收纳盒的左上角坐标, (x2,y2)为整个收纳盒右下角坐标
        cin >> m >> x1 >> y1 >> x2 >> y2;
        for (int i = 0; i < n; ++ i )
        {
            LL u, l;          // 第 i 个纸板的两端点坐标为 (uᵢ, y1) 和 (lᵢ, y2)
            scanf("%lld%lld", &u, &l); 
            a[i] = {u, y1}, b[i] = {l, y2};   // a[i]存隔板上的坐标, b[i]存隔板下的坐标  
        }
        a[n] = {x2, y1}, b[n] = {x2, y2};    // 收纳盒边界

        memset(ans, 0, sizeof ans);
        while (m -- )
        {
            LL x2, y2;                  // 每个玩具坐标
            cin >> x2 >> y2;
            ans[find(x2, y2)] ++ ;      // 对应第 i 的纸板左侧的玩具数量加一
        }

        if (is_first == false) puts("");
        is_first = false;
        for (int i = 0; i <= n; ++ i )
            cout << i << ": " << ans[i] << endl;
    } 
    return 0;
}