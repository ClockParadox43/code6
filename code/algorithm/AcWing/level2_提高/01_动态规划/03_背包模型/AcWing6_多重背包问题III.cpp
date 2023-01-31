#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 20010;

int n, m;
int f[N], g[N], q[N];

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i ++ )
    {
        int v, w, s;
        cin >> v >> w >> s;
        memcpy(g, f, sizeof f);
        for (int r = 0; r < v; r ++ )
        {
            int hh = 0, tt = -1;
            for (int k = r; k <= m; k += v)
            {
                if (hh <= tt && q[hh] < k - s * v) hh ++ ;
                while (hh <= tt && g[q[tt]] - (q[tt] - r) / v * w <= g[k] - (k - r) / v * w) tt -- ;
                q[ ++ tt] = k;
                f[k] = g[q[hh]] + (k - q[hh]) / v * w;
            }
        }
    }

    cout << f[m] << endl;

    return 0;
}
