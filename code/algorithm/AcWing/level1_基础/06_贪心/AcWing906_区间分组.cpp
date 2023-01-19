// 1) 按照左端点排序
// 2) 从前往后处理每个区间
//      判断能否将其放到某个现有的组中 
//      排序后, 贪当前点, 如果当前左端点大于 max_r 就说明没有相交
//      L[i] > Max_r, Li 在这组的区间后面
//          1) 如果不存在这样的组, 开新组, 然后将其放进去
//          2) 如果存在这样的组, 将其放入, b并更新当前组的 Max_r
// 证明:
//  1) ans <= cnt
//     首先按照这个条件得到的一定是一个合法方案(组内没有交集) 
//     ans 是所有合法方案中的最小值所以 ans <= cnt
//  2) ans >= cnt
//     假设一共有 cnt 个组, 枚举到当前区间时
//     假设之前 cnt-1 个组和当前组都有交集, 也就是说那个组 Max_r > l[i], 
//     因为 l[i] 是从小到大枚举的    
//     所以当前 l[i] 一定大于之前的 l[i]
//     同理, 类似的组也可以在别的组找到
//
//     因此就找到了 cnt-1 个区间都包含 l[i] 这个点
//     算上 l[i] 就找到 cnt 个区间, cnt 个区间的交集不为空, 即和 l[i] 公共点
//     这种情况需要另开组
//     所以得到组合方案一定是 >= cnt 的  
//
// 如何实现:
//  这样的组有一堆, 如何挑选一个组, 其实可以用小根堆来做, 如果所有 Max_r 的最小值都 > l[i]
//  那么就没有这样的组了, 需要重新开一个组. 动态维护最小 Max_r
//  
//  如果当一个组中的 Max_r 被更新, 下一个 l[i] 进组时时候会冲突
//  l 从小到大, 如果之前的 l 能入组, 那么后面的 l 只要符合条件更能入组
//  l会越来越大, 距离最小 Max_r 越来越远
//  
// 整理: 用堆维护最小 max_r, 冲突的区间会开新组, 且是 l 越来越大, 也就是说后来的区间更能进堆顶组 
//      直到该区间将组内 max_r 更新至不是最小
//
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 100010;

int n;

struct Range
{
    int l, r;
    bool operator< (const Range& W)
    {
        return l < W.l;
    }
}range[N];

void test()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        range[i] = { l, r };
    }

    // 左边变得从小到大, 此时只要再判断当前L是否大于即可
    sort(range, range + n);
    // 用堆是为了动态的维护每个组的 max_r, 如果不是动态维护需要每个区间进行枚举
    // 10 (7 9) (-4 6) (-4 -2) (-6 0) (-7 6) (1 6) (-9 6) (-5 -3) (2 10) (-10 6)
    // 比如这个样例, 排序序后依然, 两两之间有交集, 但是间隔的区间却是有没有交集的
    // 所以需要动态维护每个组
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i = 0; i < n; ++i)
    {
        auto r = range[i];      // r 表示的是区间

        // 用最小的 r 来更新该组
        // 最小值(r) >= l 的话, 说明必须要开一个新的组
        // 最小的 r 都 >= l, 说明 l 和别的 r 都用重叠, 再开一个新组 
        if (heap.empty() || heap.top() >= r.l) heap.push(r.r);
        else
        {
            // top < r.l, 说明没有交集, 更新 max_r
            int t = heap.top();
            heap.pop();
            heap.push(r.r);
        }
    }
    cout << heap.size() << endl;
}

int main()
{
    test();
    return 0;
}


