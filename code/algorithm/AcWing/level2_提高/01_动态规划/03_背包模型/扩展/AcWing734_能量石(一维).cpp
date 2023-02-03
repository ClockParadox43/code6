#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 110, M = 1e5 + 10;

struct Stone
{
    int s, e, l;
    bool operator<(const Stone &W) const {return s * W.l < W.s * l;}
}stones[N];
int T, n, m;
int f[M];

void solve()
{
    // 求恰好的背包DP, 为了保证状态都是从起点转移的, 要把非起点初始化为无穷大以避免转移
    memset(f, -0x3f, sizeof f);
    f[0] = m = 0;
    cin >> n;
    for (int i = 1; i <= n; ++ i) 
        cin >> stones[i].s >> stones[i].e >> stones[i].l, m += stones[i].s;
    sort(stones + 1, stones + 1 + n);
    for (int i = 1; i <= n; ++ i)
        for (int j = m; j >= stones[i].s; -- j) 
        {
            int pre = j - stones[i].s;  // 消耗的时间
            f[j] = max(f[j], f[pre] + stones[i].e - pre * stones[i].l);
        }
    int res = 0;
    for (int i = 0; i <= m; ++ i) res = max(res, f[i]);
    cout << res << endl;
}

int main()
{
    cin >> T; int idx = 1;
    while (T -- )
    {
        cout << "Case #" << idx ++ << ": ";
        solve();
    }
    return 0;
}
