// 枚举每个元素可以放在哪一组
// 对于第二种方法相当于是, 你把篮子放一排, 你拿着水果, 然后一个个的往下看, 看看能不能放在篮子里
// (每个数在每组中进行尝试)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 15;
vector<int> g[N];
int nums[N];
int ans = N;
int n;

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

// 如果当前数和当前组内的数互质返回 false, 否则返回 true
bool check(vector<int>& v, int x)
{
    for (int i = 0; i < v.size(); ++ i)
        if (gcd(v[i], x) > 1) return false; 
    return true;
}

// u是当前处理到序列的下标, used是目前使用的组数
void dfs(int u, int used)
{
    // 剪枝:如果当前使用的组已经>=目前获得的最优解, 停止当前分支的搜索
    if (used + 1 >= ans) return;
    
    // 如果已经看到看到了最后一个数
    if (u >= n)
    {
        ans = min(ans, used + 1);
        return;
    }

    // 先在已经使用的组中找, 看看能否插进去
    for (int i = 0; i <= used; ++ i)
        if (check(g[i], nums[u]))      // 判断当前数是否可以可以插入g[i]
        {
            g[i].push_back(nums[u]);
            dfs(u + 1, used);
            g[i].pop_back();
        }

    // 剪枝:因为n个数最多只能放进n个组, 所以总数<=n, 允许尝试放进新组
    if (used + 1 <= n)
    {
        g[used + 1].push_back(nums[u]);
        dfs(u + 1, used + 1);
        g[used + 1].pop_back();
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> nums[i];
    
    dfs(0, 0);      // 第0个数, 在第0组
    cout << ans << endl;
    return 0;
}