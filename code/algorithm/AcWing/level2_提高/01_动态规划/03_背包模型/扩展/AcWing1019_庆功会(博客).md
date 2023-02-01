######朴素版本优化
```c++
#include <iostream>

using namespace std;

const int N = 510, M = 6010;

int n, m;
int f[M];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
    {
        int v, w, s; cin >> v >> w >> s;
        for (int j = m; j >= v; -- j)
            for (int k = 0; k <= s; ++ k)
                if (j - k * v >= 0) f[j] = max(f[j], f[j - k * v] + k * w);
    }
    cout << f[m] << endl;
    return 0;
}
```

######位运算优化
```c++
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 6010;
int F[N], V[N], W[N];

int main()
{
    int n, m;
    cin >> n >> m;
    
    int cnt = 0;
    while(n --)
    {
        int v,w,s; cin >> v >> w >> s;
        for(int i = 1; i <= s; i *= 2)
            s -= i, V[cnt] = i * v, W[cnt ++ ] = i * w;
        if(s) V[cnt] = s * v, W[cnt ++ ] = s * w;
    }
    
    for(int i = 0; i < cnt; i ++)
        for(int j = m; j >= V[i]; j --)
            F[j] = max(F[j], F[j - V[i]] + W[i]);
    printf("%d",F[m]);
    return 0;
}
```
######单调队列优化
```c++
#include <iostream>
#include <cstring>

#define N 6004
using namespace std;

int n, m;
int f[N], q[N], g[N];

int main()
{
    cin >> n >> m;
    while (n -- )
    {
        int v, w, s; cin >> v >> w >> s;
        memcpy(g, f, sizeof f);
        for (int i = 0; i < v; ++ i)        // 余数
        {
            int hh = 0, tt = -1;
            for (int j = i; j <= m; j += v) // i+?v 
            {
                // g[q[tt]]-q[tt]/v*w: 表示队尾值加上偏移量后的大小
                // g[j]-j/v*w: 表示新来的数加上偏移量的大小
                if (hh <= tt && j - v * s > q[hh]) ++ hh;
                while (hh <= tt && g[q[tt]] - q[tt] / v * w < g[j] - j / v * w) -- tt;
                q[ ++ tt] = j;
                f[j] = g[q[hh]] + (j - q[hh]) / v * w;
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}
```


