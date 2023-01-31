#include <iostream>

using namespace std;
const int N = 1010;

int n, m;
int v[N], w[N];
int f[N][N];


// 完全背包:每件物品用无限次
// 用 k 来展开
// 
// 为什么多出一项:
//   因为是 f[i,j] 展开, f[i,j-v] 自己本身就是后面那项
// 
// 为什么 f[i][j-v] 第一项不加 w:
//   因为 k 从 0 开始
//   选择的情况 * 0, 相当于不选择性, w*0=0
//  
// f[i][j] = max(f[i-1][j], f[i-1][j-v]+w, f[i-1][j-2v]+2w, f[i-1][j-3v]+3w)
// f[i][j-v] = max(         f[i-1][j-v],   f[i-1][j-2v]+w,  f[i-1][j-3v]+2w)
// 
// 比 f[i][j] 多减去 1 个 v
// 抛开首项, 后面每一项都比, f[i][j-v] 多一个 w
// f[i][j] = max(f[i-1][j], f[i][j-v]+w)
// 优化1
void test()     
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
        {
            f[i][j] = f[i - 1][j];
            if (j >= v[i]) 
                f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]);      // i 位置抵消后发现依赖的是当前行
        }

    cout << f[n][m] << endl;
}

// 优化2:完全背包问题求的所有前缀的最大值
void test2()
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
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i)
        scanf("%d%d", &v[i], &w[i]);
    
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j <= m; ++ j)
        {
            f[i][j] = f[i - 1][j];
            for (int k = 0; k * v[i] <= j; ++ k)
                f[i][j] = max(f[i][j], f[i - 1][j - v[i] * k] + w[i] * k);
        }
    printf("%d", f[n][m]);
    return 0;
}





