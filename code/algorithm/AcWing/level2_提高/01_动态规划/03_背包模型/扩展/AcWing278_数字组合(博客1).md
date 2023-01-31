```c++
// 直接优化
#include <iostream>

#define N 101 
#define M 10001
using namespace std;

int n, m;
int v[N], f[M];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> v[i];
    f[0] = 1;
    for (int i = 1; i <= n; ++ i)
        for (int j = m; j >= v[i]; -- j)
            f[j] += f[j - v[i]];
    cout << f[m] << endl;
    return 0;
}
```
######朴素写法为什么从 0 开始
```c++
其实为什么j要从0开始，是一种代码变形的结果，因为大家不知道原始的形态是什么样的，所以有困惑，原始形态是这样的:
```
```c++
#include <iostream>

using namespace std;
const int N = 110;
const int M = 10010;
int n, m;
int a[N];
int f[N][M];

int main() 
{
    scanf("%d %d", &n, &m);
    //f[0][0] = 1; 
    for (int i = 0; i <= n; i++) f[i][0]=1;

    for (int i = 1; i <= n; i++) 
    {
        scanf("%d", &a[i]);
        for (int j = 1; j <= m; j++) 
        {
            f[i][j] = f[i - 1][j];
            if (j >= a[i]) f[i][j] += f[i - 1][j - a[i]];
        }
    }
    printf("%d\n", f[n][m]);
    return 0;
}
```
```c++
为什么要用循环初始化掉左侧第一列呢? 因为使用瞪眼大法知, 每一个状态, 都是从上一行的前序状态转移而来, 
而递推值开始不能是0, 只能是1, 也就是左侧第一列全要给初始值1. 之所以现在写成j=0，其实是把原始形态的代码进行了等价变形,
这样代码更短
```
######递推值开始不能是0
```c++
一个新状态f[i][j], 要么从f[i−1][j]转移过来, 要么从f[i−1][j−a[i]]转移而来, 而我们定义的属性是方案数, 所以采用了累加的办法就可以了.
这样从大到小去思考, 是不是就是大的依赖小的, 小的依赖更小的, 那么最小的就是f[0][0], 如果它是0, 我们就会发现一个很滑稽的结论, 0不管怎么累加都是0, 
最后就加了个寂寞.
似乎与乘法世界的本原是1概念是一样的, 比如我们要计算累乘积, 一定是定义初始值s=1, 然后再s=*2,s=*3,s*=4, 你把s定义成0试试, 也是乘了个寂寞
```