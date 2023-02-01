######学背包问题的过程中:
    1. 一开始学背包问题时遇到的大多数的状态表示是: 从前i个物品中选, 且总体积不超过j的问题
    2. 慢慢地在提高课中, 就有出现状态表示是: 从前i个物品中选, 且总体积恰好是j的问题. 
       例如 AcWing 1023. 买书, 求的是恰好是j的总方案数问题
    3. 同时还出现了状态表示是: 从前i个物品中选, 且总体积至少是j的问题. 
       例如 AcWing 1020. 潜水员, 求的是总体积至少是j的最小价值

    可以观察到, 他们的分析方法以及状态转移方程都是一样的, 唯独是初始化有很大的不同

####求方案数初始化总结
######二维情况
```c++
    1.体积至多j, f[0][i] = 1, 0 <= i <= m, 其余是0
    2.体积恰好j, f[0][0] = 1, 其余是0
    3.体积至少j, f[0][0] = 1, 其余是0
```
######一维情况
```c++
    1.体积至多j, f[i] = 1, 0 <= i <= m
    2.体积恰好j, f[0] = 1, 其余是0
    3.体积至少j, f[0] = 1, 其余是0 
```
####求最大值最小值初始化总结
######二维情况
```c++
    1.体积至多j, f[i,k] = 0, 0 <= i <= n, 0 <= k <= m(只会求价值的最大值)
    2.体积恰好j,
      当求价值的最小值: f[0][0] = 0, 其余是INF
      当求价值的最大值: f[0][0] = 0, 其余是-INF
    3.体积至少j, f[0][0] = 0, 其余是INF(只会求价值的最小值)
```
######一维情况
```c++
    1.体积至多j, f[i] = 0, 0 <= i <= m(只会求价值的最大值)
    2.体积恰好j,
       当求价值的最小值: f[0] = 0, 其余是INF
       当求价值的最大值: f[0] = 0, 其余是-INF
    3.体积至少j, f[0] = 0, 其余是INF(只会求价值的最小值)
```
***
####求方案数问题
`1.从前i个物品中选, 且总体积不超过j的总方案数, 初始化是f[0][i] = 1, 0 <= i <= m, 其余是0`
#####01背包
`例子: 给你一堆物品, 每个物品有一定的体积, 每个物品只能选一个, 求总体积不超过m的方案数`
```
输入
4 5
2 2 3 7
输出
7
```
######二维代码
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;
    for(int i = 0; i <= m; i ++ ) f[0][i] = 1; // 第0件物品选0件属于一种方案
    // 状态表示f[i,j]:选择前i个物品不超过j的情况下的方案数
    // 属性:cnt
    // 状态计算:
    //    选择:f[i-1,j-v]
    //  不选择:f[i-1,j]
    //  那么 f[i,j] 就是总方案数(当然,是符合条件的情况下) f[i,j] = f[i-1,j]+f[i-1,j-v]
    for(int i = 1; i <= n; i ++ )
    {
        int v; cin >> v;
        for(int j = 0; j <= m; j ++ ) 
        {
            f[i][j] = f[i - 1][j];
            if(j >= v) f[i][j] += f[i - 1][j - v];
        }
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;
    for(int i = 0; i <= m; i ++ ) f[i] = 1;
    for(int i = 1; i <= n ; i ++ )
    {
        int v; cin >> v;
        for(int j = m;j >= v;j --)
            f[j] = f[j] + f[j - v];
    }

    cout << f[m] << endl;
    return 0;
}
```
######完全背包
`例子: 给你一堆物品, 每个物品有一定的体积, 每个物品可以选无数多个, 求总体积不超过m的方案数`
```
输入
3 5
2 3 7
输出
7
```
######二维代码
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;
    for(int i = 0; i <= m; i ++ ) f[0][i] = 1; // 第0件物品选0件属于一种方案
    // 状态表示f[i,j]:前i件物品选择k件不超过体积j情况下的方案数
    //             属性:cnt
    // 状态计算:
    //      选择第i件:f[i-1][j-kv]
    //      忽略第i件:f[i-1][j]
    // f[i,j]就是选和不选的方案数总和
    for(int i = 1; i <= n; i ++ )
    {
        int v; cin >> v;
        // 因为转移方程展开一样第三层循环被优化
        for(int j = 0; j <= m; j ++ )
        {
            f[i][j] = f[i - 1][j];
            if(j >= v) f[i][j] += f[i][j - v];
        }
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;
    for(int i = 0; i <= m; i ++ ) f[i] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        int v; cin >> v;
        for(int j = v; j <= m; j ++ ) 
            f[j] = f[j] + f[j - v];
    }

    cout << f[m] << endl;
    return 0;
}
```
`2.从前i个物品中选, 且总体积恰好是j的总方案数, 初始化是f[0][0] = 1, 其余是0`
#####01背包
`例子: 给你一堆物品, 每个物品有一定的体积, 每个物品只能选一个, 求总体积恰好是m的方案数`
```
输入
4 5
2 2 3 7
输出
2
```
######二维代码
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;
    f[0][0] = 1;            // 选择第0件物品体积恰好是0的方案有1个
    // 状态表示f[i,j]:前i件物品中选择体积恰好是j的所有方案数
    //           属性:cnt
    // 状态计算:
    //      选择第i件:f[i-1][j-v]
    //      忽略第i件:f[i-1][i]
    // f[i,j]就是选和不选的方案数总和
    // 可以看出, 转移方程是一样的, 但 所表达的含义不一样, 初始化不一样
    // 上一个是 "总体积不超过j的总方案数", 这个是 "总体积恰好是j的总方案数"
    for(int i = 1; i <= n; i ++ )
    {
        int v; cin >> v;
        for(int j = 0; j <= m; j ++ )
        {
            f[i][j] = f[i - 1][j];
            if(j >= v) f[i][j] += f[i - 1][j - v];
        }
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;
    f[0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        int v; cin >> v;
        for(int j = m; j >= v; j -- )
            f[j] = f[j] + f[j - v];
    }

    cout << f[m] << endl;
    return 0;
}
```

#####完全背包
`例子: 给你一堆物品, 每个物品有一定的体积, 每个物品可以选无数多个, 求总体积恰好是m的方案数`
```
输入
3 5
2 3 7
输出
1
```
######二维代码
```c++
// 因为和前面差不多, 就不写了
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;
    f[0][0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        int v; cin >> v;
        for(int j = 0; j <= m; j ++ )
        {
            f[i][j] = f[i - 1][j];
            if(j >= v) f[i][j] += f[i][j - v];
        }
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;
    f[0] = 1;
    for(int i = 1; i <= n; i ++)
    {
        int v; cin >> v;
        for(int j = v; j <= m; j ++ )
            f[j] = f[j] + f[j - v];
    }

    cout << f[m] << endl;
    return 0;
}
```
`3. 从前i个物品中选, 且总体积至少是j的总方案数, 初始化是f[0][0] = 1, 其余是0(至少的情况, j需要从0枚举到m，或者从m枚举到0)`
#####01背包
`例子: 给你一堆物品, 每个物品有一定的体积, 每个物品只能选一个, 求总体积至少是m的方案数`
```
输入
3 5
2 3 7
输出
11
```
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N][N];

int main()
{
    // 终点 "至少" 包含负数的情况
    cin >> n >> m;
    f[0][0] = 1;
    for(int i = 1; i <= n ; i ++ )
    {
        int v; cin >> v;
        // 即使物品体积比j大, j - v < 0, 也能选, 等价于f[i - 1][0], 
        // "至少" 要选择这么多, 负数说明已经满足了, 但是负数会越界, 所以和0取max
        for(int j = 0; j <= m; j ++) 
            f[i][j] = f[i - 1][j] + f[i - 1][max(0,j - v)];
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;
    f[0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        int v; cin >> v;
        for(int j = m; j >= 0; j -- ) // 即使物品体积比j大, j - v < 0, 也能选, 等价于f[0]
            f[j] = f[j] + f[max(0,j - v)];
    }

    cout << f[m] << endl;
    return 0;
}
```
#####完全背包
`例子: 给你一堆物品，每个物品有一定的体积, 每个物品可以选无数多个, 求总体积至少是m的方案数, 答案是无穷多种方案数`
***
####求最大值最小值问题
`1.从前i个物品中选, 且总体积不超过j的最大价值, 初始化是f[i,k] = 0, 0 <= i <= n, 0 <= k <= m(只会求价值的最大值)`
#####01背包问题
`例子: 给你一堆物品, 每个物品有一定的体积和对应的价值, 每个物品只能选一个, 求总体积不超过m的最大价值`
```
输入
4 5
1 2
2 4
3 4
4 5
输出
8
```
######二维代码
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i ++ )       // 枚举物品
    {
        int v, w; cin >> v >> w;
        for(int j = 0; j <= m; j ++ )   // 枚举体积, 从前i-1个物品中选出最大价值
        {
            f[i][j] = f[i - 1][j];
            if(j >= v) f[i][j] = max(f[i][j], f[i - 1][j - v] + w); 
        }
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++
#include <iostream>

using namespace std;

const int N = 110;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i ++ )
    {
        int v, w; cin >> v >> w;
        for(int j = m; j >= v; j -- )
            f[j] = max(f[j], f[j - v] + w);
    }

    cout << f[m] << endl;
    return 0;
}
```
`2. 从前i个物品中选, 且总体积恰好是j`
#####01背包问题
```c++
(1)求价值最小值：初始化f[0][0] = 0, 其余是INF
```
`例子: 给你一堆物品, 每个物品有一定的体积和对应的价值, 每个物品只能选一个, 求总体积恰好是j的最小价值`
```
输入
4 5
1 2
2 4
3 4
4 5
输出
7
```
######二维代码
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;

    memset(f, INF, sizeof f);       // 因为求的是最小, 全部初始化成正无穷 
    f[0][0] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        int v, w; cin >> v >> w;
        for(int j = 0; j <= m; j  ++ )
        {
            f[i][j] = f[i - 1][j];
            if(j >= v) f[i][j] = min(f[i][j], f[i - 1][j - v] + w);
        }
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;

    memset(f, INF, sizeof f);
    f[0] = 0;

    for(int i = 1; i <= n; i ++)
    {
        int v, w; cin >> v >> w;
        for(int j = m; j >= v; j -- )
            f[j] = min(f[j], f[j - v] + w);
    }

    cout << f[m] << endl;
    return 0;
}
```
```c++
(2)求价值最大值: 初始化f[0][0] = 0, 其余是-INF
```
`例子: 给你一堆物品, 每个物品有一定的体积和对应的价值, 每个物品只能选一个, 求总体积恰好是j的最大价值`
```
输入
4 5
1 2
2 4
3 4
4 5
输出
8
```
######二维代码
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;    

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;

    memset(f, -INF, sizeof f);  // 因为求的是最大, 全部初始化成负无穷 
    f[0][0] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        int v, w; cin >> v >> w;
        for(int j = 0; j <= m; j ++ )
        {
            f[i][j] = f[i - 1][j];
            if(j >= v) f[i][j] = max(f[i][j], f[i - 1][j - v] + w);
        }
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++

#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;

    memset(f, -INF, sizeof f);
    f[0] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        int v, w; cin >> v >> w;
        for(int j = m; j >= v; j -- )
            f[j] = max(f[j], f[j - v] + w);
    }

    cout << f[m] << endl;
    return 0;
}

```
######完全背包问题
```c++
(1)求价值最小值: 初始化f[0][0] = 0, 其余是INF
```
`例子: 给你一堆物品, 每个物品有一定的体积和对应的价值, 每个物品可以选无数多个, 求总体积恰好是j的最小价值`
```
输入
4 5
1 2
2 4
3 4
4 5
输出
7
```
######二维代码
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;

    memset(f, INF, sizeof f);
    f[0][0] = 0;        // 第0件物品选择k件体积为0

    for(int i = 1; i <= n; i ++ )
    {
        int v, w; cin >> v >> w;
        for(int j = 0; j <= m; j ++)
        {
            f[i][j] = f[i - 1][j];
            if(j >= v) f[i][j] = min(f[i][j], f[i][j - v] + w);
        }
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;

    memset(f, INF, sizeof f);
    f[0] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        int v, w; cin >> v >> w;
        for(int j = v; j <= m; j ++ )
            f[j] = min(f[j], f[j - v] + w);
    }

    cout << f[m] << endl;

    return 0;
}
```
```c++
(2)求价值最大值：初始化f[0][0] = 0, 其余是-INF
```
`例子: 给你一堆物品, 每个物品有一定的体积和对应的价值, 每个物品可以选无数多个, 求总体积恰好是j的最大价值`
```
输入
4 5
1 2
2 4
3 4
4 5
输出
10
```
######二维代码
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;

    memset(f, -INF, sizeof f);
    f[0][0] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        int v, w; cin >> v >> w;
        for(int j = 0; j <= m; j ++ )
        {
            f[i][j] = f[i - 1][j];
            if(j >= v) f[i][j] = max(f[i][j], f[i][j - v] + w);
        }
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;

    memset(f, -INF, sizeof f);
    f[0] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        int v, w; cin >> v >> w;
        for(int j = v; j <= m; j ++ )
            f[j] = max(f[j], f[j - v] + w);
    }

    cout << f[m] << endl;
    return 0;
}
```
`3.从前i个物品中选, 且总体积至少是j, 初始化是f[0][0] = 0, 其余是INF(只会求价值的最小值)`
`例子:给你一堆物品, 每个物品有一定的体积和对应的价值, 每个物品可以选无数多个, 求总体积至少是j的最小价值(AcWing 1020. 潜水员)`
```
输入
4 5
1 2
2 4
3 4
4 5
输出
10
```
######二维代码

```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int f[N][N];

int main()
{
    cin >> n >> m;

    memset(f, INF, sizeof f);
    f[0][0] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        int v, w;
        cin >> v >> w;
        for(int j = 0; j <= m; j ++ )
            f[i][j] = min(f[i - 1][j], f[i][max(0, j - v)] + w);//即使物品体积比j大，j - v < 0，也能选，等价于f[i - 1][0]
    }

    cout << f[n][m] << endl;
    return 0;
}
```
######一维代码
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int f[N];

int main()
{
    cin >> n >> m;

    memset(f, INF, sizeof f);
    f[0] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        int v, w; cin >> v >> w;
        for(int j = m; j >= 0; j -- )
            f[j] = min(f[j], f[max(0, j - v)] + w);// 即使物品体积比j大，j - v < 0，也能选，等价于f[0]
    }

    cout << f[m] << endl;
    return 0;
}
```