// 完全背包:每件物品用无限次

#include <iostream>
#include <algorithm>

using namespace std;

// N 个物品, 容量是 V
const int N = 1010;

int n, m;
int v[N], w[N];
int f[N];


void test()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];

    // 依赖的是当前行, 所以内层循环可以升序进行遍历
    for (int i = 1; i <= n; ++i)
        for (int j = v[i]; j <= m; ++j)
        {
            // 前 i-2~1 的数组已经没用了
            // 删除 i,i-1 行
            // 恒等式无效删除 
            // f[i][j] = f[i-1][j];
            // f[j] = f[j];
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }

    cout << f[m] << endl;
}


int main()
{
    test();
    return 0;
}

