// 有n个人, 每个人手上有个字符串s, 他们想将字符串改成t, t可能在别人手上, 问每个人是否可以都拿到自己想要的
// 很明显的图联通问题, 抽象成给定一个有向图, 图中是否有环, 可以用并查集或者拓扑序来考虑判环, 这里采取了并查集写法
#include <iostream>
#include <unordered_map>

using namespace std;
const int MAXN = 200010;

int p[MAXN], n, m, id;
string x, y;
unordered_map<string, int> mp;

int find(int x)
{
    if (x != p[x])
        return p[x] = find(p[x]);
    return p[x];
}

int main()
{
    int n; scanf("%d", &n);
    bool f = true;
    for (int i = 1; i < 2 * n; ++ i) p[i] = i;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> x >> y;
        if (!mp[x]) mp[x] = ++ id;      // 为每个节点标记序号
        if (!mp[y]) mp[y] = ++ id;
        int px = find(mp[x]);   // 找到该节点的爹
        int py = find(mp[y]);
        if (px != py) p[px] = py;   // 不一样就合并, 有环说明多次合并
        else f = false;             // 标记为 false
    }

    puts(f ? "Yes" : "No");
    return 0;
}