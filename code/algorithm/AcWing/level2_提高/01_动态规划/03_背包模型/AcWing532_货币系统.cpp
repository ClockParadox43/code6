// 这题是一道线性代数问题
// 求解一个向量组的秩(最大无关向量组的向量个数)
// 但是代码写起来就是一个模拟筛的过程
// 从小到大, 先查看当前数有没有被晒掉
// 1)如果没有就把它加入到最大无关向量组中, 并把他以及他和此前的硬币的线性组合都筛掉
// 2)如果有就不理会
// 即就是在完全背包求方案数的过程中, 统计那些初始没有方案数的物品
// 这样就变成一个完全背包问题了
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 103, M = 25004;

int T, n;
int a[N], f[M];

int main()
{
    cin >> T;
    while (T -- )
    {       
        cin >> n;
        for (int i = 0; i < n; ++ i) cin >> a[i];
        sort(a, a + n);
        memset(f, 0, sizeof f);
        // 我们只需统计所有物品的体积是否能被其他的线性表出
        // 因此背包的体积只需设置为最大的物品体积即可
        // res用来记录最大无关向量组的个数
        int m = a[n - 1]; f[0] = 1;
        int res = 0;
        // 从小枚举到大, 类似线性筛
        for (int i = 0; i < n; ++ i)
        {
            if (!f[a[i]]) res ++ ;      // 如果当前的方案没有任何方案的话, res 就要加1
            for (int j = a[i]; j <= m; ++ j)
                f[j] |= f[j - a[i]];
        }
        // 输出最大无关向量组的向量个数
        cout << res << endl; 
    }
    return 0;
}
