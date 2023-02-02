// 可以将每个主件及其附件看作一个物品, 记主件为p, 两个附件为 a,b
// 则一共最多4种组合:
//  1.p
//  2.p,a
//  3.p,b
//  4.p,a,b
// 这四种组合是互斥的, 最多只能从中选一种, 因此可以将每种组合看作一个物品, 那么问题就变成了分组背包问题
// 在枚举四种组合时可以使用二进制的思想, 可以简化代码
// 
// 时间复杂度:
// 分组背包的时间复杂度是 物品总数 * 总体积，因此总时间复杂度是 O(Nm)
//
// 思路:主件当做物品组, 组件和附件的搭配看做物品组内的物品
#include <iostream>
#include <vector>

#define fs first
#define sc second

using namespace std;
typedef pair<int, int> pii;
const int N = 60, M = 32010;

int n, m;
pii a[N];
vector<pii> b[N];  // 主件(下标)对应的附件
int f[M];

int main()
{
    cin >> m >> n;  // 体积, 物品个数
    for (int i = 1; i <= n; ++ i)
    {
        int v, p, q;    // 价格, 重要度, 主/附
        cin >> v >> p >> q;
        p *= v;         // 使得 p*v最大
        if (!q) a[i] = {v, p};
        else b[q].push_back({v, p}); // 存进q号主件的附件, 下标不能从0开始, 0被主件的表示占用
    }
    for (int i = 1; i <= n; ++ i)      // 枚举物品
        for (int u = m; u >= 0; -- u)   // 枚举体积
        {
            // 制做分组背包问题某类里每一个可选择的单元————打包
            // for循环里的b[i].size()筛选了只有主件会进入循环, 附件不能进入
            // 二进制枚举物品组内的所有打包单元的状态, 共2的n次方种, 用j表示每一种, j的第k位1/0表示第k个附件选/不选
            for (int j = 0; j < 1 << b[i].size(); ++ j) // 枚举主件的每一种状态
            {
                // 当前这个打包单元的体积是v, 价值是w, 下面这几行代码就是在计算 v 和 w
                int v = a[i].fs, w = a[i].sc;           // 主件必选
                for (int k = 0; k < b[i].size(); ++ k)  // 枚举状态j的每一位
                    if (j >> k & 1)     // 如果j的第k位是1, 说明包含第k个附件
                    {
                        v += b[i][k].fs;    // 累加上附件的价格
                        w += b[i][k].sc;    // 累加上附件的pv
                    }
                // 枚举完该主件的其中一个状态后, 已经计算出v和w, 做分组背包问题的状态计算
                if (u >= v) f[u] = max(f[u], f[u - v] + w);
            }
            // 然后枚举主件和别的附件搭配的下一个状态
        }
    cout << f[m] << endl;
    return 0;
}