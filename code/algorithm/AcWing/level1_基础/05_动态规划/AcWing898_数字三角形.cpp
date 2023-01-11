// 从顶部出发, 在每一结点可以选择移动至其左下方的结点或移动至其右下方的结点 
// 一直走到底层, 要求找出一条路径, 使路径上的数字的和最大
// 数据范围
// 1 ≤ n ≤ 500,
// −10000 ≤ 三角形中的整数 ≤ 10000
//
// 状态表示 f[i][j]: 从起点出发, 来到当前第 f[i,j] 的路径的值
//          属性: Max
//          集合: 从左上路径来到当前 (i,j) 位置, 从右上路径来到当前 (i,j) 位置
// 状态计算: 
//          1) 从左上来到当前位置: a[i,j] + f[i-1,j-1]
//          2) 从右上来到当前位置: a[i,j] + f[i-1,j]
//
// 时间复杂度: O(n^2)
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 510, INF = 1e9;

int n;
int a[N][N];
int f[N][N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i )
        for (int j = 1; j <= i; ++ j )
            cin >> a[i][j];
    
    // memset(f, -0x3f, sizeof f);
    // 处理边界, 因为边界是 0 
    // 为什么要初始化到 i+1, 因为会枚举到 f[i-1][j] 然而第 i-1 层的 j
    // 比第 i 层少 1, 所以每一层的 i+1 也要初始化
    for (int i = 1; i <= n; ++ i )
        for (int j = 0; j <= i + 1; ++ j )
            f[i][j] = -INF;
    
    // 下一层对于上一层都必须无缝枚举到, 所以是 f[i-1][j-1], f[i-1][j]
    // f[i-1][j], f[i-1][j + 1], 会又漏洞, 画图即可知道
    f[1][1] = a[1][1];
    for (int i = 2; i <= n; ++ i )
        for (int j = 1; j <= i; ++ j )
            f[i][j] = max(f[i - 1][j] + a[i][j], f[i - 1][j - 1] + a[i][j]);
    
    int ans = f[n][1];
    for (int i = 2; i <= n; ++ i )
        ans = max(ans, f[n][i]);

    cout << ans << endl;
    
    return 0;
}