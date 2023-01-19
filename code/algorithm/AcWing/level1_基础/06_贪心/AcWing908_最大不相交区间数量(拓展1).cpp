// 即排完序后的线段, 在数组位置靠前线段左端点 < 数组位置靠后线段的左端点.
// 即对于每个线段i, 要找到一个 j 使得, Li > Rj(loclast + 1 <= j < i),
// 所以我们搞个前缀 min 就行了

#include <iostream>
#include <algorithm>

using namespace std; 
typedef pair<int, int> PII;
const int MAXN = 100005;

int n; 
PII s[MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i)
        scanf("%d%d", &s[i].first, &s[i].second);
    
    // 排完序后, 数组位置靠前线段左端点 < 数组靠后线段的左端点
    sort(s + 1, s + n + 1);
    
    // 对于每个线段 Li(last), 找到一个线段 Rj
    // 为什么取 min 不取 max ?
    //      - 当进 if 的时候, 说明当前枚举的区间和上一次最后的区间有交点 
    //        取 min 我们让左端点慢慢延长, 如果出现了, Li > maxR 的情况, 说明不相交
    //        并且 Li 的 右端点一定大于 maxR, 这时候我们就可以将前面枚举的那一坨作为一个线段
    //        然后开始新的枚举
    int ans = 1, maxR = s[1].second;
    for (int i = 2; i <= n; ++ i)
        if (s[i].first <= maxR)         // 如果当 "前线段的左端点" 小于 "最右侧线段" 他们的右端点 min 作为maxR
            maxR = min(maxR, s[i].second);
        else ans ++ , maxR = s[i].second;   // 当前的 l 和 r 不相交的情况
    
    cout << ans << endl;
    return 0;
} 