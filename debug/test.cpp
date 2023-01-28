#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 104;

int T, n;
int w[MAXN], f[MAXN];

int main()
{
    scanf("%d", &T);
    while (T -- )
    {
        memset(f, 0, sizeof f), memset(w, 0, sizeof w);
        
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i) scanf("%d", &w[i]);
        reverse(w, w + n);

        for (int i = 0; i < n; ++ i)
        {
            f[i] = 1;
            for (int j = 0; j < i; ++ j)
                if (a[i] > a[j]) f[i] = max(f[i], f[j] + 1);
        }

        int ans = f[0];
        for (int i = 1; i < n; ++ i)
            ans = max(ans, f[i]);
        
        printf("%d", ans);
    }

    return 0;
}

