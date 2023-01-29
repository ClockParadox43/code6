// q2: 找到够数量的上升子序列
//     贪心
// 389 207 155 300 299 170 158 65
// 让剩下子序列结尾的数尽可能大
// 贪心流程:
//   p1: 如果现有子序列的结尾都小于当前数, 则创建新子序列
//   p2: 将当前数放到结尾大于等于它的最小子序列后面


#include <iostream>

using namespace std;

const int MAXN = 1e3 + 4;

int n, ans, ansl;
int w[MAXN];
int g[MAXN], f[MAXN]; // g[]:存储当前已经开好的子序列的数, 每次去寻找 >= g[k] 的最小的数

int main()
{
    while (cin >> w[n]) n ++ ;
    for (int i = 0; i < n; ++ i)
    {
        f[i] = 1;
        for (int j = 0; j < i; ++ j)    
            if (w[i] <= w[j]) f[i] = max(f[i], f[j] + 1);
        ans = max(ans, f[i]);
    }
    printf("%d\n", ans);
    
    // 求有几组最长下降子序列
    // g[]:存储现有递减子序列结尾的数
    // cnt:当前子序列个数
    // 让剩下子序列结尾的数尽可能大
    // 贪心流程:
    //   p1: 如果现有子序列的结尾都小于当前数, 则创建新子序列
    //   p2: 将当前数放到结尾大于等于它的最小子序列后面
    // 为什么能这么做?
    //      因为序列只能往后选择嘛, 一定有一组递减序列是以某个数结尾, 如果 "当前数更大"
    //      只能从新开序列
    for (int i = 0; i < n; ++ i)
    {
        int k = 0;
        while (k < ansl && w[i] > g[k]) k ++ ;  // 如果 "现有子序列" 小于 "当前要判断的数", 说明 "这组递减子序列" 在单调上升
        g[k] = w[i];
        if (k >= ansl) ansl ++ ;
    }
    printf("%d\n", ansl);
    return 0;
}