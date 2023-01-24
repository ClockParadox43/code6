// [s,t] -> 将指定线段完全覆盖
// 输入最小区间数, 无法覆盖输出 -1
// 思路: 有序的覆盖, 如果到达那个 >= 目标区间终点, 就输出最小
//       否则 -1

// 1) 将所有区间按左端点从小到大排序
// 2) 从前往后一次枚举各个区间, 在所有能覆盖 start 的区间中, 选择右端点最大区间
//    然后将 start 更新成右端点最大值
//
// ans <= cnt
//   每次选择的右端点一定在下一个区间的左端点右边
//   将方案中选择出的区间数量记作 cnt, ans 代表所有可行方案中的最小值
//   所以 ans 定小于某个可行解的区间数量
// 
// ans >= cnt
// 证明见微信


#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;

struct Range
{
    int l, r;
    bool operator< (const Range& W) const
    {
        return l < W.l;
    }
}range[N];

int main()
{
    int st, ed;
    scanf("%d%d", &st, &ed);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        range[i] = { l,r };
    }

    sort(range, range + n);

    // 1) 按照左端点排序
    // 2) 在覆盖之前区间的情况下, 选择可以覆盖 st 的新区间, 且它的右端点更大
    int res = 0;
    bool success = false;
    for (int i = 0; i < n; )
    {
        int j = i, r = -2e9;

        // 在左端点能够覆盖的情况下求最长右端点
        while (j < n && range[j].l <= st)
        {
            r = max(r, range[j].r);
            ++j;                      // 枚举下一个区间
        }

        // 如果这段能衔接起来的区间的最大右端点无法超过之前的右端点
        // 说明不存在可以覆盖这块区间的线段
        if (r < st) break;
         
        // 找到一个覆盖当前 st 的端点
        ++res;                     

        if (r >= ed)
        {
            success = true;
            break;
        }

        st = r;
        i = j;          // i 从 j 找到的区间继续枚举

       // i = j - 1; 下个循环还会再加一次, 保证下次循环是从 j 开始, 防止区间存在漏洞
    }

    if (!success) res = -1;

    cout << res << endl;

    return 0;
}

