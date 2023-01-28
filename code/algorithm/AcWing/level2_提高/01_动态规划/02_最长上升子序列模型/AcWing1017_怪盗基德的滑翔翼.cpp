// LIS问题

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110, INF = 1e8;

int a[N];
int f[N];

int main()
{
    int q;
    scanf("%d", &q);
    
   
    // 因为起点可以任意, 即正着求一遍最长下降子序列
    // 再倒着求一遍最长上升子序列
    while (q -- )
    {
        int n;
        scanf("%d", &n);
        
        for (int i = 1; i <= n; ++ i ) scanf("%d", &a[i]);
        
        // 求以 i 结尾的最长下降子序列
        for (int i = 1; i <= n; ++ i ) 
        {
           f[i] = 1;
           for (int j = 1; j < i; ++ j )
               if (a[j] > a[i]) 
                    f[i] = max(f[i], f[j] + 1);
        }
        
        int res = -1;
        for (int i = 1; i <= n; ++ i ) res = max(res, f[i]);
         
        memset(f, -INF, sizeof f);
        // 倒着求一遍最长上升子序列
        for (int i = n; i >= 1; -- i )
        {
            f[i] = 1;
            for (int j = n; j > i; -- j )
                if (a[j] > a[i])            // j 在后面, 后面的必须大于前面的所以是最长上升子序列
                    f[i] = max(f[i], f[j] + 1);
        }
        
        for (int i = 1; i <= n; ++ i ) res = max(f[i], res);
        cout << res << endl;
    }

    return 0;
}