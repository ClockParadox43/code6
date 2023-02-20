// 题目大意:给定n个正整数, 将它们分组, 每组中任意两个数互质
//          输出最小整数
// 本质是一个最优化问题, 我们要求所有方案中的最小值
//
// 思路:1) 把某个数加到最后一个组中
//      2) 如果该数和组内数不互质, 就开新组
//
// 第一种方法就相当于是, 你把水果任意的排成一排, 
// 然后拿着一个篮子从第一个水果开始一个个的往后看, 看看能能放到你的这个篮子中
#include <iostream>

using namespace std;

const int N = 10;

int n, ans = N; // 由于是求最小值, 这里初始化为最大值 
int a[N];       // n个数
int g[N][N];    // 分组
int st[N];

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

bool check(int g[], int x, int start)
{
    for (int i = 0; i < start; ++ i)
        if (gcd(g[i], x) > 1) return false;
    return true;
}

// gr:当前要分在哪个组, gc:要放在该分组的哪个位置, start:从哪个位置开始选择元素(组合套路, 定一个遍历顺序)
// cnt: 已经分组完毕的元素个数  
void dfs(int gr, int gc, int start, int cnt)
{
    if (gr >= ans) return;    // 剪枝:如果当前组数大于最优解, 直接返回, 有时分组分布下去, 组内数看着会重复
    if (cnt == n) ans = gr;   // 所有数已经看完了

    bool flag = true;   // 从start开始找, 是否有元素不能放到gr中
    for (int i = start; i < n; ++ i)
        if (!st[i] && check(g[gr], a[i], gc))   // 如果当前数没有被选择, 检查a[i]是否可以放在该组
        {
            st[i] = true;       // 标记
            g[gr][gc] = a[i];   // 将a[i]放在当前组第gc个位置
            dfs(gr, gc + 1, i + 1, cnt + 1);
            st[i] = false;
            flag = false;
        }

    // 新开一个分组

    // 由于dfs每层之间确定了顺序, 所以期间是会有元素被漏掉的, 【 比如一开始你找的一串序列(1)是1,2,3,4 但是第二次(2)是1,3,4 很显然此时
    // (2)还有一个3没有得到分组, 需要从start=0开始再把它找出来!  因此这样做仿佛有点浪费时间呢!! 】
    
    // 因此当所有元素都不能放进当前分组的时候 或者 当start=n-1了但是元素没有全部分组完毕时, 要重新从start=0开始找, 并且一定要有st数组!!!
    // 不然会把一个元素重复的分组!
    if(flag) dfs(gr + 1 ,0, 0, cnt);
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> a[i];
    
    // 为什么一开始gr从1开始, 但是分组只开到10呢?
    // 首先这样的话, 可以直接通过gr就能得到当掐分了多少组
    // 其次ans的初始化为10
    dfs(1, 0, 0, 0);
    cout << ans << endl;
    return 0;
}