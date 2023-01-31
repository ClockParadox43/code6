```c++
实际上我们并不需要二维的dp数组，适当的调整循环条件，我们可以重复利用dp数组来保存上一轮的信息

我们令 dp[j] 表示容量为j的情况下，获得的最大价值
那么，针对每一类物品 i ，我们都更新一下 dp[m] --> dp[0] 的值，最后 dp[m] 就是一个全局最优值

dp[m] = max(dp[m], dp[m-v] + w, dp[m-2*v] + 2*w, dp[m-3*v] + 3*w, ...)

接下来，我们把 dp[0] --> dp[m] 写成下面这种形式
dp[0], dp[v],   dp[2*v],   dp[3*v],   ... , dp[k*v]
dp[1], dp[v+1], dp[2*v+1], dp[3*v+1], ... , dp[k*v+1]
dp[2], dp[v+2], dp[2*v+2], dp[3*v+2], ... , dp[k*v+2]
...
dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j]
```
```c++
显而易见，m 一定等于 k*v + j，其中  0 <= j < v
所以，我们可以把 dp 数组分成 j 个类，每一类中的值，都是在同类之间转换得到的
也就是说，dp[k*v+j] 只依赖于 { dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j] }

因为我们需要的是{ dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j] } 中的最大值，
可以通过维护一个单调队列来得到结果。这样的话，问题就变成了 j 个单调队列的问题
```

```c++
所以，我们可以得到
dp[j]    =     dp[j]
dp[j+v]  = max(dp[j] +  w,  dp[j+v])
dp[j+2v] = max(dp[j] + 2w,  dp[j+v] +  w, dp[j+2v])
dp[j+3v] = max(dp[j] + 3w,  dp[j+v] + 2w, dp[j+2v] + w, dp[j+3v])
...
但是，这个队列中前面的数，每次都会增加一个 w ，所以我们需要做一些转换
```
```c++
dp[j]    =     dp[j]
dp[j+v]  = max(dp[j], dp[j+v] - w) + w
dp[j+2v] = max(dp[j], dp[j+v] - w, dp[j+2v] - 2w) + 2w
dp[j+3v] = max(dp[j], dp[j+v] - w, dp[j+2v] - 2w, dp[j+3v] - 3w) + 3w
...
这样，每次入队的值是 dp[j+k*v] - k*w
```
```c++
单调队列问题，最重要的两点
1) 维护队列元素的个数，如果不能继续入队，弹出队头元素
2) 维护队列的单调性，即：尾值 >= dp[j + k*v] - k*w

本题中，队列中元素的个数应该为 s+1 个，即 0 -- s 个物品 i
```
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 20010;

int n, m;
int f[MAXN], g[MAXN], q[MAXN]; 

int main()
{
    cin >> n>> m;
    for (int i = 0; i < n; ++ i)
    {
        memcpy(g, f, sizeof f);
        int v, w, s;
        cin >> v >> w >> s;
        for (int j = 0; j < v; ++ j)        // 枚举余数
        {
            int hh = 0, tt = -1;            // 滑窗模板
            for (int k = j; k <= m; k += v) 
            {
                // 我们维护的是单调队列的长度 sv, 其实元素有 s+1 个, 包括选择 0~s 个物品的体积,
                // 类比原单调队列模板时, 要注意模板中的长度指的就是元素个数, 所以类比到这也就可以按照元素个数思考, 
                // 得出维护长度的代码 if(hh<=tt&&k-q[hh]+v>(s+1)*v)hh++;
                // 化简: if(hh<=tt&&k-q[hh]>sv)hh++;
                // 也就是当元素大于当前组的余数时, 弹出队头, 因为单调队列的长度单位是v,我们把+1类比成+v
                if (hh <= tt && k - s * v > q[hh]) ++ hh;
                while (hh <= tt & g[q[tt]] - (q[tt] - j) / v * w <= g[k] - (k - j) / v * w) -- tt;
                if (hh <= tt) f[k] = max(f[k], g[q[hh]] + (k -  q[hh]) / v * w);
                q[ ++ tt] = k; 
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}
```