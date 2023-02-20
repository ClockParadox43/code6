// 求最大的最小
// 空题越长, 老师的怒气值越高, 花费的时间越少
// 在空题尽可能长的情况下求花费的最少时间
#include <iostream>
#include <cstring>

using namespace std;

const int N = 50010, INF = 1e9;
int n, m;
int w[N], q[N], f[N];

bool check(int k)
{
    f[0] = 0;
    int hh = 0, tt = 0;
    for (int i = 1; i <= n; ++ i)
    {
        if (hh <= tt && q[hh] < i - (k + 1)) ++ hh;
        f[i] = f[q[hh]] + w[i];
        while (hh <= tt && f[q[tt]] >= f[i]) -- tt;
        q[ ++ tt] = i;
    }

    int res = INF;
    for (int i = n - k; i <= n; ++ i) 
        res = min(res, f[i]);

    return res <= m;
}

int main()
{
    cin >> n >> m;

    // 输入抄第i题所花费的w[i]分钟
    for (int i = 1; i <= n; ++ i) cin >> w[i];  
    
    // 所花费的时间尽可能短, 所以r二分过来
    int l = 0, r = n;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    cout << l << endl;
    return 0;
}