// 最少可以用多少个上升子序列和下降子序列
// 暴力枚举当前数, 放在上升子序列中好, 还是放在下降子序列中好
//
// dfs 求最小值
// 1) 记录全局最小不断更新
// 2) 不断迭代加深 

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 60;

int n, ans;
int q[N];
// up: 存储当前所有上升子序列的末尾元素
// down: 存储当前所有下降子序列的末尾元素
int up[N], down[N];     

// u:当前枚举到第几个数
// su:当前枚举到的上升子序列的个数
// st:当前枚举到的下降子序列的个数
void dfs(int u, int su, int sd)
{
    // 说明答案不可能再变小了, 直接返回
    if (su + sd >= ans) return;
    // 已经枚举到最后一个数了
    if (u == n)
    {
        ans = min(ans, su + sd);
        return;
    }

    // p1:将当前数放到上升子序列中
    // k:用来记录 down/up 的组数
    int k = 0;
    // 上升子序列:记录某个长度结尾的最小值, 之后的元素一定能接在最小值后面
    // 如果当前序列比当前数大, 就加1
    // 当前序列比当前数小就加入
    while (k < su && up[k] >= q[u]) ++ k;       // 搜索能插在哪一组的后面
    int t = up[k];                              // 备份现场
    up[k] = q[u];                               // 将当前数据更新到某一组后面或者另开新组

    // 搜索完毕后, 如果 k 没有超过 su 的最大组数
    // 则说明当前搜索的点能接在当前搜索的上升子序列的末尾 
    if (k < su) dfs(u + 1, su, sd);             
    else dfs(u + 1, su + 1, sd);                // 否则开启新组
    up[k] = t;                                  // 还原现场

    // p2:将当前数放到下降子序列中
    // 下降子序列:记录某个长度结尾的最大值, 之后的元素一定能接在最大值后面
    k = 0;
    while (k < sd && down[k] <= q[u]) ++ k;
    t = down[k];
    down[k] = q[u];
    if (k < sd) dfs(u + 1, su, sd);     // 搜索完毕后, 如果 k没有超过 sd 的最大组数,则说明当前搜索的点能接在当前搜索的下降子序列的末尾
    else dfs(u + 1, su, sd + 1);        // 开新的组
    down[k] = t;
}

int main()
{
    while (cin >> n, n)
    {
        for (int i = 0; i < n; ++ i) cin >> q[i];

        ans = n;
        dfs(0, 0, 0);       // 初始状态遍历了 0 个数, 最长上升子序列中 0 组数, 最长下降子序列中 0 组数

        cout << ans << endl;
    }
    return 0;
}