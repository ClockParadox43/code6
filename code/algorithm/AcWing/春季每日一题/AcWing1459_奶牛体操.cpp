
// 求达标数对出现的次数

#include <iostream>

using namespace std;

const int N = 25;


int s[N][N], q[N];      // s:记录出现过的数对

int main()
{
    int n, m; scanf("%d%d", &n, &m);
    
    for (int i = 1; i <= n; ++ i )
    {
        for (int j = 1; j <= m; ++ j )
            scanf("%d", &q[j]);
        
        for (int j = 1; j <= m; ++ j )
            for (int k = j + 1; k <= m; ++ k )
                s[q[j]][q[k]] ++ ;
    }
    
    int ans = 0;
    for (int i = 1; i <= m; ++ i )
        for (int j = 1; j <= m; ++ j )
            if (s[i][j] == n) ++ ans;
    
    cout << ans;
    
    return 0;
}