// 危险系数 = 当前牛上面所有牛的重量之和 - 当前牛的强壮值
// 解: 按照 wi+si 从小到大的顺序排, 危险系数一定是最小的

#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN = 50010;
typedef pair<int, int> pii;

int n;
pii cow[MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i)
    {
        int w, s; scanf("%d%d", &w, &s);
        cow[i] = {w + s, w};
    }
    
    // 按照 wi+si 排序
    sort(cow, cow + n);
    
    int res = -2e9, sum = 0;
    for (int i = 0; i < n; ++ i)
    {
        int w = cow[i].second, s = cow[i].first - w;
        res = max(res, sum - s); // 之前牛的总重量 - 当前牛的强壮值 = 危险系数
        sum += w;   // sum 每次从小到大加上重量值
    }

    printf("%d\n", res);
    return 0; 
}
