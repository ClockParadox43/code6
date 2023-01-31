```c++

多重背包原始转移方程:
    f[i, j] = max(f[i-1,j], f[i-1,j-v]+w   ,...,         f[i-1,j-sv]+sw)
   f[i,j-v] = max(          f[i-1,j-v],   f[i-1,j-2v]+w, f[i-1,j-sv]+(s-1), f[i-1,j-v-sv]+sw);
   可以发现, 多重背包的两个转移方程项数不对应...所以不能使用完全背包的优化
```

```c++
但是, 我们可以把这个式子继续推导下去, 知道背包体积用到不能用为止
    f[i,j] = max(f[i-1,j], f[i-1][j-v]+w ,..., f[i-1,j-sv]+sw)
    f[i,j-v] = max(        f[i-1,j-v], f[i-1][j-2v]+w,...,f[i-1,j-(s+1)v]+sw);
    f[i,j-2v] = max(                   f[i-1,j-2v], f[i-1,j-2v]+w, f[i-1,j-(s+2)v]+sw)
    ...
    f[i,r+sv] = max(f[i-1,r+sv], f[i-1,r+(s-1)v]+w,...,f[i-1,r]+sw) 
    f[i,r+(s-1)v] = max(f[i-1,r+(s-1)v],..,f[i-1,r]+(s-1)w)
    ...
    f[i,r+2v] = max(f[i-1,r+2v],f[i-1,r+v]+w,f[i-1,r]+2w)
    f[i,r+v] = max(f[i-1,r+v],f[i-1,r]+w);
    f[i,r] = f[i-1,r]
        ps:余数越来越大
    
    其中 r = j mod vi, 也可以理解为 "完全背包" 下把当前物品选到不能再选后, 剩下的余数得到 f[i,r] = f[i-1,r] 后, 
    我们利用"完全背包优化思路"往回"倒推一遍"
    会发现一个 "滑动窗口求最大值的模型", 具体如下:
```
```c++
为方便观察, 将 f[i-1,j] 改成 f[i]
    
    f[i,r] = f[r]
    f[i,r+v] = max(fᵣ₊ᵥ, fᵣ+w)
    f[i,r+2v] = max(fᵣ₊₂ᵥ, fᵣ₊ᵥ+w, fᵣ+2w)
    ...
    f[i,r+(s-1)v] = max(fᵣ₊₍ₛ₋₁₎ᵥ,fᵣ₊₍ₛ₋₂₎ᵥ+w, fᵣ₊₍ₛ₋₁₎w)
    f[i,r+sv] = max(fᵣ₊ₛᵥ, fᵣ₊₍ₛ₋₁₎ᵥ+,...,fᵣ+sw) (滑动窗口已满)
    f[i,r+(s+1)v] = max(fᵣ₊₍ₛ₊₁₎ᵥ, fᵣ₊ₛᵥ+w,...,fᵣ₊ᵥ+sw) (滑动窗口已满)
    ...
    f[i,j-2v] = max(fⱼ₋₂ᵥ, fⱼ₋₃ᵥ+w,...,fⱼ₋₍ₛ₊₂₎ᵥ+sw) (滑动窗口已满)
    f[i,j-v] = max(fⱼ₋ᵥ, fⱼ₋₂ᵥ+w,..,fⱼ₋₍ₛ₊₁₎+sw) (滑动窗口已满)
    f[i,j] =  max(fⱼ, fⱼ₋ᵥ+w,...,sⱼ₋ₛᵥ+sw) (滑动窗口已满)
```
```
可能看上去还是有点复杂, 为了再方便大家观察, 我们去掉 w, 然后把数组展开成一条链

具体如下图:
```
<img src="https://cdn.acwing.com/media/article/image/2021/06/15/55909_fa6e36f6cd-%E5%A4%87%E6%B3%A8-2020%E5%B9%B47%E6%9C%8825%E6%97%A5.png" alt="图片alt" title="图片title">

```c++
于是通过"滑动窗口", 我们能在"线性"的时间里求出 i阶段里, 所有满足 j ≡ r mod(v) 的 f[i,j]
"滑动窗口" 求最大值的实现, 只需利用队列在队头维护一个 "最大值"的单调递减队列即可, 
为了更新所有"i"阶段里的状态 f[i,j], 我们只需要额外枚举所有"余数r"
```
```
不要忘记, 滑动窗口内部比较最大值的时候, 有一个在之前了方便观察, 被删掉的偏移量w, 记得加上再比较
    具体就是 "当前下标" 和该 "最大值的下标" 之间差 'x' 个 'v', 那么就要在上 'x' 个 'v'
    在上面公式里, 还是比较容易看出的
```
####二维朴素:
```c++
#include <iostream>

using namespace std;

const int N = 1010, M = 20010;

int n, m;
int v[N], w[N], s[N];
int f[N][M];
int q[M];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> v[i] >> w[i] >> s[i];
    // 明确优化的最初想法: 从上一行的前 s+1 项加上 q*w 中选取最大值(0<=q<=s), 
    // 当然这个s不一定能取到，后面涉及的地方会细说
    for (int i = 1; i <= n; ++ i)
    {
        // 枚举余数:当考虑第i类物品时, 也就是计算到第i行时
        // 对于体积j, 我们考虑的是j, j-v直到r这些列,r是j%v的余数,r取值0~v-1
        // 对于行来说,%r可以得到不同的同余类(一直减r,直到r减不开)
        // 所以我们要枚举每个r, 然后不断加上一个v, 即可挑出这些列
        // 为什么不从大到小枚举这些列? 我们要挑出的是最大值, 所以自然要从小到大枚举
        for (int r = 0; r < v[i]; ++ r)
        {
            int hh = 0, tt = -1;
            for (int j = r; j <= m; j += v[i]) // 固定住r, 枚举r+?v
            {
                // 我们维护的单调队列的长度是 s*v, 其中元素有s+1个,包括0~s个物品的体积
                // 类比原单调队列: 要注意模板中的元素其实是之元素个数, 所以类比到这也就可以按照元素个数思考
                // 得出维护长度的代码 if(hh<=tt&&j-q[hh]+v>(s+1)*v)
                // 化简得到: if(hh<=tt&&j-q[hh]>s*v)
                // 位移一下可以得到 q[hh] < j-s*v 
                if (hh <= tt && j - q[hh] > s[i] * v[i]) hh ++ ;
                // 判断单调队列递增的, 右边的好说, 就是f[i-1][j], 左边的是指其他项的最大值, 
                // 因为每个相邻的式子差了w[i], 所以到当前状态差了的w[i]的个数为(j-q[tt])/v[i]
                while (hh <= tt && f[i - 1][q[tt]] + (j - q[tt]) / v[i] * w[i] <= f[i - 1][j]) -- tt;

                // q[tt]=r+k*v(r+k*v在队列中, 代表的就是下标), 
                // 对应在上一层中的值为: g[r+k*v]-k*w 
                // (k表示物品数量, 因为多出 k 件物品也要减去 k 件物品的价值)
                q[ ++ tt] = j;
                
                // q[hh]:?v的总体积
                // 单调队列最大值, 加上相对j的偏移量
                // (j - q[hh]) / v[i]:算出x个v, 再加上x个v的价值
                f[i][j] = f[i - 1][q[hh]] + (j - q[hh]) / v[i] * w[i];
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}
```
####一维优化:
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1010, MAXM = 20010;

int n, m;
int v[MAXN], w[MAXM], s[MAXN];
int f[MAXM], g[MAXM];
int q[MAXM];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> v[i] >> w[i] >> s[i];
    for (int i = 1; i <= n; ++ i)
    {
        memcpy(g, f, sizeof g);
        for (int r = 0; r < v[i]; ++ r)
        {
            int hh = 0, tt = -1;
            for (int j = r; j <= m; j += v[i])
            {
                if (hh <= tt && j - q[hh] > s[i] * v[i]) hh ++ ;
                while (hh <= tt && g[q[tt]] + (j - q[tt]) / v[i] * w[i] <= g[j]) -- tt;
                q[ ++ tt] = j;
                f[j] = g[q[hh]] + (j - q[hh]) / v[i] * w[i];
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}
```
####一维优化:
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1010, MAXM = 20003;

int n, m;
int v[MAXN], w[MAXN], s[MAXN];
int f[2][MAXM];
int q[MAXM];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> v[i] >> w[i] >> s[i];
    for (int i = 1; i <= n; ++ i)
        for (int r = 0; r < v[i]; ++ r)
        {
            int hh = 0, tt = -1;
            for (int j = r; j <= m; j += v[i])
            {
                if (hh <= tt && j - q[hh] > s[i] * v[i]) hh ++ ;
                while (hh <= tt && f[(i - 1) & 1][q[tt]] + (j - q[tt]) / v[i] * w[i] <= f[(i - 1) & 1][j]) tt -- ;
                q[ ++ tt] = j;
                f[i & 1][j] = f[(i - 1) & 1][q[hh]] + (j - q[hh]) / v[i] * w[i]; 
            }
        }
    cout << f[n & 1][m] << endl;
}
```