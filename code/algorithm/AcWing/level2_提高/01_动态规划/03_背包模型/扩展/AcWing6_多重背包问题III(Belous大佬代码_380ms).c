#include <stdio.h>

const int N = 20001;
struct node
{
    int pos, val;
}q[N];
int dp[N];

int main()
{
    int n, m; scanf("%d%d", &n, &m);
    while (n--)
    {
        int v, w, s; scanf("%d%d%d", &v, &w, &s);
        for (int j = 0; j < v; ++ j)
        {
            int hh = 0, tt = 0, stop = (m - j) / v;
            //[hh, tt)
            for (int k = 0; k <= stop; ++k)
            {
                int val = dp[k * v + j] - k * w;
                while (hh < tt && val >= q[tt - 1].val) --tt;
                q[tt].pos = k, q[tt ++ ].val = val;
                if (q[hh].pos < k - s) ++hh;
                dp[v * k + j] = q[hh].val + k * w;
            }
        }
    }
    printf("%d\n", dp[m]);
    return 0;
}