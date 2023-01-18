#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;
const int MAXN = 1e6 + 3;


int n, m, l, r, a[MAXN], b[MAXN];
LL sum, ans;

// 按照数位之和的升序排序
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> a[i];
    cin >> m;
    while (m -- )       // 输入的同时处理差分
        cin >> l >> r, b[l] ++ ; b[r + 1] -- ;
    
    // 先得到数组 c (仍存放在数组 b 中), 在顺便统计原来的总和 sum
    for (int i = 1; i <= n; ++ i)
    {
        b[i] += b[i - 1];
        sum += (LL) a[i] * b[i];  
    }

    // 分别排序
    sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);
    
    for (int i = 1; i <= n; ++ i)
        ans += (LL) a[i] * b[i;]    
    cout << ans - sum;
    return 0;
}