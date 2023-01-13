
#include <iostream>

using namespace std;
const int MAXN = 100005;

int n;
int t[MAXN], x[MAXN], y[MAXN];

int main()
{
    scanf("%d", &n);

    // (0,0)点是起始位置
    for (int i = 1; i <= n; ++i)
        cin >> t[i] >> x[i] >> y[i];

    bool flag = true;
    for (int i = 1; i <= n; ++i)
    {
        // 当前时间 - 之前时间 = 剩余时间
        int dt = t[i] - t[i - 1];   
        // 到目标的曼哈顿距离(求的就是到目标的最短距离)
        int dist = abs(x[i] - x[i - 1]) + abs(y[i] - y[i - 1]);     
        if (dt < dist) flag = false;
        // 如果曼哈顿距离是偶数/奇数,那么剩余时间也要是偶数/奇数
        // 如果你满足这个条件, 你总是可以到达, 同时充分利用 "去或回去"
        if (dist % 2 != dt % 2) flag = false;
    }

    if (flag) puts("Yes");
    else puts("No");
    return 0;
}





