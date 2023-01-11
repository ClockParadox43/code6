// 01背包问题:要么用要么不用, 每件物品只能使用一次
// 第 i 个物品在重量为 j 的情况下选和不选 
// 体积:v[i]
// 价值:w[i]

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
int v[N], w[N];
int f[N];


void test()
{
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];

    // 1) 更新 f[i][j] 只用到 f[i-1][j] 层
    //    f[i-2] ~ f[0] 没有用
    // 
    // 2) 一个是 j, 一个是 j-v[i], 不管哪个都是 <= j 的
    //    这并没有在 j 的两侧
    //
    // 所以, 可以用滚动数组来做
    for (int i = 1; i <= n; ++i)
        for (int j = m; j >= v[i]; --j)
        {
            // f[i][j] = f[i - 1][j];  
            // 做等价变形
            // f[j] = f[j];    
            // 恒等式直接删
            // 
            // 只有依赖 i-1 位置的时候才是严格判断每种可能性答案
            // 当 j < v[i] 的时候, 判断 false, 直接跳过
            // 所以 0~v[i-1] 的时候是无意义的
            // if (j >= v[i]) 去掉判断 
            // 
            // f[j - v[i]] 算的是左边的, 利用左边的值往后推
            // 如果从小到大递增就会内层循环算出的就是下一层的
            // 直接删其实算出的是 f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]);
            // 然而我们要算的是 f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
            // 
            // 解决:从大到小枚举
            // 从大到小枚举, 这时候左边的值还没有被更新 
            // 依赖的是左边格子的值, 所以当前层左边格子得晚点更新
            // 倒着来即可, 对比的也是左边格子
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }

    cout << f[m] << endl;
}

int main()
{
    test();
    return 0;
}

