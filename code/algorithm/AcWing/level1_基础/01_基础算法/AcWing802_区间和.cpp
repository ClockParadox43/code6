// 应用场景:
// 假定有一个无限长的数轴, 数轴上每个坐标上的数都是 0
// 现在，我们首先进行 n 次操作，每次操作将某一位置 x 上的数加 c
// 接下来, 进行 m 次询问, 每个询问包含两个整数 l 和 r, 你需要求出在区间 [l, r] 之间的所有数的和
// 
// 数据范围
// −109 ≤ x ≤ 109,
// 1≤n,m ≤ 105,
// −109 ≤ l ≤ r ≤ 109,
// −10000 ≤ c ≤ 10000
// 
// 数据范围: 最多只会用到 n 个下标 x, 每个 x 的范围做多在 -10^9~10^9
//          一共有最多有 10^5 这样的 x, 对于询问操作有 2 个下标[l,r], 询问操作 2n
//          n + 2n = 30^5          
// 
// 离散化: 值域很大, 但是个数很少
// - 离线处理 对于在线查询的操作,通过离线化处理,可以一次处理多次询问
// - 离散化 观察数据范围,将数据范围大的元素转而离散成数据范围小的形式
//   属于离线查询
// 主要思路 : 将所有需要操作的数字读进来, 将里面用到的下标全部离散化
//
// 问题1. 原数组 a[] 中可能有重复元素
// 问题2. 如何算出 a[] 每个值映射的值是多少(有序离散化 -> 二分)
// 只要下标 x 对应的值在 [l,r] 内就可以将这个范围内的 x 累加, 所以可以采用有序的方式离散化
// 1) 先找到离散化后的值, 下标 x 离散化后变成 -> k, 也就是 a[k] += c
// 2) 查询操作同理, 假设求 [l,r] 区间所有数的和, 将 [l,r] 离散化到对应的下标里 [kl,kr], 即求 a[kl,kr] 区间中的和
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;

int n, m;
int a[N], s[N];         // a[] 原数组, s[] 前缀和数组
vector<int> alls;       // 存储离散化后的结果
vector<PII> add, query; 

// 将 x 映射到从 1 开始的自然数的位置
int find(int x)
{
    int l = 0, r = alls.size() - 1;
    while (l < r)
    {
        int m = l + r >> 1;
        if (alls[m] >= x) r = m;
        else l = l + 1;   
    }

    return l + 1; // 舍弃 0 位置, 因为要用到前缀和, 前缀和从 1 开始不需要处理边界
}

// 1) 读入所有数据, 将用到的下标的下标全部离散化
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i )
    {
        int x, c;
        scanf("%d%d", &x, &c);      // 在 x 位置插入 c
        add.push_back({x, c});      
        alls.push_back(x);          // 插入 x 
    }

    // 读入所有查询区间
    for (int i = 0; i < m; ++ i )   
    {
        int l, r;
        scanf("%d%d", &l, &r);
        query.push_back({l, r});

        alls.push_back(l);          // 将左右区间加入待离散化的数组
        alls.push_back(r);
    }

    // alls 中的所有下标{x,l,r}都并到了一起

    // 去重
    // unique : 将所有不重复元素放到数组前面去, 返回新数组的最后一个位置
    // erase : 将 新数组位置~数组最后位置下标全部删掉 
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());

    // 找到了离散化后值, 在该位置 +c
    // x = x+1 
    for (auto item : add)
    {
        int x = find(item.first);    
        a[x] += item.second;
    }

    // 预处理前缀和
    for (int i = 1; i < alls.size(); ++ i ) s[i] = s[i - 1] + a[i];
}
