#include <iostream>

using namespace std;

const int N = 100010;

int a[N], s[N];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++ i ) scanf("%d", &a[i]);
    
    int ans = 0;
    // i 枚举往右扩
    for (int i = 0, j = 0; i < n; ++ i ) 
    {
        s[a[i]] ++ ;
        // 一旦大于 1 就将之前记录去掉
        while (s[a[i]] > 1) 
        {
            s[a[j]] -- ;
            ++ j;               // 最后会停在为 1 的地方, 所以是左闭右闭
        }
        ans = ans > (i  - j  + 1) ? ans : (i - j + 1);
    }
    
    printf("%d", ans);
    
    return 0;
}