// (dp)O(nkt)
// 稍加思考后(指打表)就可以发现, 当且仅当一张货币面额可以被该系统下其他货币表示时
// 此货币对该系统能表示的面额没有影响, 换言之这个货币没有存在的必要, 所以将这类的货币
// 从系统中去除就可以得到等价的最小数量货币系统
// 可以用dp求出能表示该面额的方案数, 若对于一张货币方案数唯一(即只能被自己表示) 则这张货币不能
// 被省略, 反之可以被省略, 最后统计一下就行了

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 105, M = 25005;
int n, k;
int a[N], f[M];
int ans, t;

int main()
{
    cin >> t;
    while (t -- )
    {
        cin >> n;
        memset(a, 0, sizeof a);
        memset(f, 0, sizeof f);
        f[0] = 1;
        k = 0;      // k 为最大可以表示的数
        for (int i = 1; i <= n; ++ i) { cin >> a[i]; k = max(k, a[i]);}
        for (int i = 1; i <= n; ++ i)
            for (int j = a[i]; j <= k; ++ j)
                f[j] += f[j - a[i]];
        int ans = 0;
        for (int i = 1; i <= n; ++ i)
            if (f[a[i]] == 1) ans ++ ;
        cout << ans << endl;
    }
}