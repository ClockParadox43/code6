```
在本一道题当中, 我们可以看到若此题为多重背包问题, 那么按照数据范围来看, 其实可以用多重背包问题2的方法来水过, 
先将01背包, 完全背包转化成多重背包, 01背包的话, 则可以将物品数量写成1, 
而完全背包, 则数量为(总体积(V)/该物品的体积(v[i]), 
再按照多重背包的思路, 即将多重背包转化成一个个的二进制01背包来做即可
```
```c++
#include <iostream>

using namespace std;

const int N = 100010;
int n, m;
int v[N], w[N], f[N];

int main()
{
    cin >> n >> m;
    int cnt = 1;
    for (int i = 1; i <= n; ++ i)
    {
        int a, b, s; cin >> a >> b >> s;
        int k = 1;
        if (s < 0) s = 1;
        else if (!s) s = m / a;
        // 把01背包和完全背包先转化成多重背包, 
        // 若为完全背包, 则在最优情况下, 
        // 只能取总体积/该物品体积向下取整 
        while (k <= s)
            v[cnt] = a * k, w[cnt ++ ] = b * k, s -= k, k *= 2;
        if (s)
            v[cnt] = s * a, w[cnt ++ ] = s * b;
    }
    // 将多重背包进行二进制优化, 变成01背包
    for (int i = 1; i <= cnt; ++ i)
        for (int j = m; j >= v[i]; -- j)    
            f[j] = max(f[j], f[j - v[i]] + w[i]);
    cout << f[m] << endl;
    return 0;
}

```