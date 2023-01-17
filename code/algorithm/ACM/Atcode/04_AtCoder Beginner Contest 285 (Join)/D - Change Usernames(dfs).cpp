#include <iostream>
#include <unordered_map>
#include <vector>

#define fst first
#define scd second

using namespace std;
typedef long long LL;
typedef pair<string, string> PSS;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;

    int cnt = 1;        // 统计有一个点 / 为每个点标记序号
    vector<PSS> a(n);       
    unordered_map<string, int> id;  // 为每个点标记序号
    for (int i = 0; i < n; ++ i)
    {
        cin >> a[i].fst >> a[i].scd;                // fst 有指向 scd 的边
        if (!id[a[i].fst]) id[a[i].fst] = cnt ++ ;  // 如果 fst 的 id 为 0(说明没来过), 那么 fst 的序号就加一
        if (!id[a[i].scd]) id[a[i].scd] = cnt ++ ;  // 如果 scd 的 id 为 0(说明没来过), 那么 scd 的序号就加一
    }

    // 建立图
    // 通过过 a[i] 取出第 i 个字符串取出存在 id 中的点, 用 g 来存 
    // 让 fst 的点指向 scd 的点
    vector<vector<int>> g(cnt + 1);
    for (int i = 0; i < n; ++ i)
        g[id[a[i].fst]].push_back(id[a[i].scd]);

    bool ok = true;
    vector<bool> vis(cnt + 1);  // 左闭右开
    
    function<void(int, int, int)> dfs = [&](int u, int fa, int cnt)
    {
        if (cnt && u == fa)     // cnt:防止刚进循环时候, u == fa
        {                       // 下一层开始, 一进循环就先判断, 孩子是否等于父亲, 也就是说孩子有指向父亲的边
            ok = false;         // 父亲在递归中不会发生改变(忘了可以自己画图)
            return;
        }

        for (auto v : g[u])  // 遍历当前 u 行, g是二维数组, 自己可以指向 v
        {       
            vis[v] = true;          // 当前孩子标记为 true 
            dfs(v, fa, cnt + 1);    // 然后遍历孩子那一层, 看看孩子是否指向父亲, 有的话就返回
        }
    };

    // 遍历每个点
    // 枚举每一个父亲是否被有别的点指向
    for (int i = 1; i < cnt; ++ i)
        if (!vis[i] && ok)
        {
            vis[i] = true;
            dfs(i, i, 0);
        }
    
    if (ok) cout << "Yes\n";
    else cout << "No\n";
    
    return 0;
}