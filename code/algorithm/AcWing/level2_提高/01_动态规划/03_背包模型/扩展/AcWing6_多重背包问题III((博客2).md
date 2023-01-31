```c++
    因为,每次循环都只需要用到 i-1 层的结果, 所以在这里:
    f[]:第 i 层结果
    g[]:第 i-1 层结果

    因为枚举到第i个物品时,要将f[0~m]的状态全部都更新一遍.所以在这里
    f[j]为体积为j的情况下获得价值的最大值,对于每一个物品i来说都要更新f[0]~f[m]的值,枚举完i个物品之后,f[m]就是最优解.
    讲到这里先举个例子,0~11可以如何表示出来呢?答:
    0 3 6 9 
    1 4 7 10            -> 余数为 1 的一组
    2 5 8 11
    所以f[0]~f[m]的状态也可以这样表示出来:
    f[0], f[v],   f[2*v],   f[3*v],   …… , f[k*v]
    f[1], f[v+1], f[2*v+1], f[3*v+1], …… , f[k*v+1]
    f[2], f[v+2], f[2*v+2], f[3*v+2], …… , f[k*v+2]
    ...
    f[r], f[v+r], f[2*v+r], f[3*v+r], …… , f[k*v+r]
    其中0<r<v,如果有f[x]中, x>m的, 会在代码中被筛除, 其中m=k*v+x;(0<x<=r);
```
######等式化简完后我们在来看看所需要的数据结构:
```c++
可以由上方的推导的公式可以知道每次入队时的数为:
q[tt]=r+k*v(r+k*v在队列中, 代表的就是下标), 对应在g[]中的值为: g[r+k*v]-k*w(k表示物品数量, 因为多出 k 件物品也要减去 k 件物品的价值)
单调队列中对比队尾大小时因对比q[tt]所对应g[]中的值
所以比较的代码为:
while (hh<=tt&&g[r+k1*v]-(r+k1*v-r)/v*w<=g[r+k*v]-(r+k*v-r)/v*w)--tt;
即:
while (hh<=tt&&g[q[tt]]-(q[tt]-r)/v*w<=g[j]-(j-r)/v*w)--tt;
如果总共有3件物品的话:
```
<img src="https://cdn.acwing.com/media/article/image/2020/12/06/42785_ea631c7637-QQ%E6%B5%8F%E8%A7%88%E5%99%A8%E6%88%AA%E5%9B%BE20201206162006.png" alt="图片alt" title="图片title">
```c++
所以在q数组中需要保证长度为s.因为每次队首都是最大值,所以状态转移方程为:
f[j]=g[q[hh]]+(j-q[hh])/v*w;
```

```c++
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 20088;

int n, m;
int f[MAXN], g[MAXN], q[MAXN];
// f 存储的是第 i 层, g 存储第 i-1 层, q 存储的是 f, 
// g[]中的下表: 体积, 例:q[5]=r+3v 

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
    {
        int v, w, s; cin >> v >> w >> s;
        memcpy(g, f, sizeof f);       // 复制上一层结果
        for (int r = 0; r < v; ++ r)  // 枚举余数, 这样形成的窗口不会超过余数
        {
            int tt = -1, hh = 0;      // tt:队尾, hh:队头(最大的)
            for (int j = r; j <= m; j += v)     // 枚举体积(单调队列模板)
            {
                while (hh <= tt && q[hh] < j - s * v) ++ hh;    // 判断是否超过 s 件物件
                /*
                    j 是体积, sv 是 s 件物品的体积, j-sv 就是余数
                    q[hh]要小于该组余数

                    如果q[hh]恰好等于r的话,j=s*v+r时,j-s*v=r,此时正好有s个物品
                    q[hh]=j-s*v,如果有s+1个物品时,j=(s+1)*v+r-s*v=r+v,大于r,就
                    超过了物品范围范围;r+2v同理,如果j=(s+2)+r是则正好有s件物品
                    通过等式,如果j=(s+3)v+r则有s+1间物品,无法通过等式.
                */
                while(hh <= tt && g[q[tt]] - (q[tt] - r) / v * w <= g[j] - (j - r) / v * w) --tt;
                /*
                    q[tt]=r+k*v(r+k*v在队列中, 代表的就是下标), 对应在g[]中的值为: g[r+k*v]-k*w(k表示物品数量, 因为多出 k 件物品也要减去 k 件物品的价值)
                    单调队列中对比队尾大小时因对比q[tt]所对应g[]中的值
                    所以比较的代码为:
                    while (hh<=tt&&g[r+k1*v]-(r+k1*v-r)/v*w<=g[r+k*v]-(r+k*v-r)/v*w)--tt;
                    即:
                    while (hh<=tt&&g[q[tt]]-(q[tt]-r)/v*w<=g[j]-(j-r)/v*w)--tt;
                */
                
                q[ ++  tt] = j;
                /*
                因为f[j]=max(g[j],g[j-v]+w,····)其中g[j]也是需要参与的,所以更新应放在
                前面,否则如果g[j]恰好是最大的的方案,那么会导致结果的错误;
                */
                f[j] = g[q[hh]] + (j - q[hh]) / v * w;//更新最大的值
           }
        }
    }

    cout<<f[m]<<endl;//输出最终结果
    return 0;
}

```