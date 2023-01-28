// 条件1: 每个城市上只能建一座桥
// 条件2: 桥与桥之间不能相交
// 条件3: 只有友好城市才能建桥
//  目标: 最多能建多少座桥
//
// 用一个结构体存两岸的城市, 按着下面坐标从小到大排序, 之后对上面的城市座一个最长上升子序列即可
#include <iostream>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int,int> PII;

const int N = 50010;

int n;
int f[N];
PII p[N];

int main()
{
    //input
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> p[i].x >> p[i].y;
    //sort
    sort(p + 1, p + n + 1);
    //dp
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j < i; ++ j)
            if (p[j].y < p[i].y) f[i] = max(f[i], f[j] + 1);
    //find result
    int res = 0;
    for (int i = 1; i <= n; ++ i) res = max(res, f[i]);
    //output
    cout << res << endl;
    return 0;
}
