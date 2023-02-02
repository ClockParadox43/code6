`如果要专门地去证明b中的元素都是a中选取的可能会有点困难, 这里提供一个比较简单的思考方向`
####约定记号:
```c++
vis[x] = true 表示 x 能够被当前 b 中的元素表示出
朴素的想法是先将 a 从小到大排序, 记 a 最小的元素为mina
```
#####分析
```c++
我们能够比较简单地知道 b 中必含有mina:   // 因为b要组成a
显然如果 b 中含有比 mina 小的元素, 那么这个元素对应的数是 a 所能组成的数的空间所没有的
与题意不符, 同时, 倘若 b 中的元素都比 mina 大, 那么b所能组成的数的空间一定不包含mina, 也矛盾.

所以b中第一个元素就是mina
此时, 我们可以更新一下vis数组: 将vis[mina * k] (k为正整数) 全部标记为 true

接下来, 继续考察排好序的a:
如果a的第二个数x对应的vis[x]是 true, 那么自然不需要进入b中(而且这样不是最优解)
如果a的第二个数x对应的vis[x]是 false, 那么一定要进入b中:

因为如果不进入:
那么我们必须要找到一个数val(进入b中)使得mina+k*val=x, 那么此时val一定是小于x的, 
故vis[val] = true，而a所能组成的数的空间不包含val, 矛盾.

按照这样的策略, 可以依次将a中的元素放入b中.
```

```c++

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 50005;

int T, n;
int vis[N], a[105];

int main()
{
    cin >> T;
    while (T -- )
    {
        memset(vis, 0, sizeof vis);
        cin >> n;
        for (int i = 1; i <= n; ++ i) cin >> a[i];
        sort(a + 1, a + 1 + n);

        int maxv = -1;
        for (int i = 1; i <= n; ++ i) maxv = max(maxv, a[i]);
        
        // a[i] 能够被自己的倍数组成
        // a[i] 能够被 t*a[i]+x组成
        // 从b筛出a的所有组成的元素, 暴力
        int cnt = 0;
        for (int i = 1; i <= n; ++ i)
        {
            if (vis[a[i]]) continue;  // 如果a中的元素被组成过就结束当前循环
            else cnt ++ ;
            for (int j = 0; j <= maxv; ++ j)
                if (vis[j]) vis[j + a[i]] = 1;  // 如果j被组成过, 那么j+a[i]也能被组成
            for (int j = a[i]; j <= maxv; j += a[i])  // j 每次加上a的倍数
                vis[j] = 1;
        }
        cout << cnt << endl;
    }   
}
```