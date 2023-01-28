
// 思路: 
// 这是一种类似贪心的解法, 第一次选择最大的, 然后把最大路径上的数字都置为空, 第二次再选择最大的
// 但这种解法有一种问题, 第一次选择最大的时候, 可能会影响第二次的选择, 导致了整体的最优受到影响
// 为了让整体的值更大, 所以我们得小心地选, 尽量避免影响第二条路径. 因此这第一次选择的路径不一定是值最大的路径
// 所以这种二次选择的解法是不可行的
// 
// 为什么不能分开走:
// 分开两次走(贪心): 第一次走到 (n, n) 求出最大值并记录路径令路径上点收益为 0 后再走一次.
// 第一次走为局部最优并且也对第二次走造成了影响, 第二次走是在第一次影响下所能走的局部最优
// 不具备 "无后效性", 因此分开两次走并不是全局最优解
// 
// 因为第一次走的时候有可能有好几条路径都是第一次的解, 而你分开走只能选择其中的一条. 
// 很不幸的是, 第一次走过的地方会被重置成 0.
// 而你不确定的是: 第一次同样是最优解, 而未被你选择的情况下, 第二次的值会不会比你已经得出的答案要大.
//
// 转移记录:
// 1. 备份原来对图
// 2. 记录最大值转移二来的坐标
// 3. 置空选择坐标中的值
#include <iostream>
#include <cstring>

#define MAXN 15
using namespace std;

typedef pair<int, int> pii;

int n, x, y, c, cnt;
int f[MAXN][MAXN], backup[MAXN][MAXN];
pii st[MAXN][MAXN];      // 记录转移过来到上个状态

int main()
{
    cin >> n;
    while (cin >> x >> y >> c, x || y || c) f[x][y] = c;
    
    memcpy(backup, f, sizeof f);    // 将原来的图进行备份
    
    int res = 0;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            if (f[i - 1][j] > f[i][j - 1])      // 如果从上来到"值"大于从左来到"值"
            {
                st[i][j] = {i - 1, j};    // 记录路径坐标
                f[i][j] += f[i - 1][j];   // 机上这个坐标到值
            }
            else
            {
                st[i][j] = {i, j - 1};
                f[i][j] += f[i][j - 1];
            }
    
    // 置空最大路径上已经取走的数
    // 最终会走到 n, 从 n 开始转移
    int i = n, j = n;
    while (i || j)
    {
        int x = i, y = j;
        backup[i][j] = 0;
        i = st[x][y].first, j = st[x][y].second;
    }

    // 再动归一遍
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            backup[i][j] += max(backup[i - 1][j], backup[i][j - 1]);
    
    cout << backup[n][n] + f[n][n] << endl;

    return 0;
}