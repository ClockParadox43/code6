// 1) 将每个区间按右端点从小到大排序
// 2) 如果往后依次枚举每个区间
//      如果当前区间中已经包含点, 则直接 pass
//      否则, 选择当前区间的右端点
//
// 证明两个值和最优解相等 -> A == B
// 证明 A >= B
//      A <= B
// 
// A<=B:
// ans 每次都是贪的都是当前最小值
// cnt:当前选择的点的个数
// cnt代表所有可行的方案, ans代表可行方案中的最小值
// 
// A>=B:
// 包含该点直接 pass, 所以下一个选择点的区间和上一个选择点的区间没有交集
// 之后选择的点以此类推
// 想把区间覆盖至少需要 cnt 个点
// 所以说所有的可行方案的点数一定大于 cnt

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;

struct Range
{
    int l, r;
    bool operator<(const Range& W) const
    {
        return r < W.r;
    }
}range[N];

void test()
{
    scanf("%d", &n);
    // 初始化区间
    for (int i = 0; i < n; ++i)
    {
        int r, l;
        scanf("%d%d", &l, &r);
        range[i] = { l, r };
    }

    sort(range, range + n);

    // 右端点只会小~大
    // 1) 如果有被包含的区间就 pass
    // 2) 没有交集的区间选择
    int res = 0, ed = -2e9;
    for (int i = 0; i < n; ++ i)
        if (range[i].l > ed)            // 当前区间左端点 > 上个区间的右端点
        {
            res ++ ;
            ed = range[i].r;
        }

    cout << res << endl;
}

int main()
{
    test();
    return 0;
}