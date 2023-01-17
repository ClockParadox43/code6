#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <unordered_map> 
#include <vector>
#include <queue>

using namespace std;

// b->m->d
// a->b-c->a 
// 看不懂自己话图, 画图不难发现, 第二种就是个环
// 点与点之间互相依赖所, 以我们无论从哪个点开始
// 都不能找到一条不被依赖的点
int main()
{
    int n; cin >> n;
    vector<string> ss(n), ts(n);
    unordered_map<string, int> dg;  // 入度
    unordered_map<string, vector<string>> g; // 图

    for (int i = 0; i < n; ++ i)
    {
        cin >> ss[i] >> ts[i];
        g[ss[i]].push_back(ts[i]);      // ss[i] 有一条指向 ts[i] 的边      
        dg[ts[i]] ++;     // ts的入度加1
    }

    queue<string> q;
    int cnt = 0;
    for (auto && [k, v] : dg)               // 入度为 0 的先入队列
        if (v == 0) q.push(k), cnt ++ ;

    while (q.size())
    {
        auto u = q.front(); q.pop();   // 去出入度为 0 的点  
        for (auto & v : g[u])   // 遍历当前点指向的边, ts 的边减 1
            if ( -- dg[v] == 0) q.push(v), cnt ++ ;  // 如果入度为 0 就入栈, 形成 top 序 
    }

    // top 序每个点都看一次, 那么一定有 n-1 条边, 如果统计的边不相等, 那么就是不成立·
    cout << (cnt == dg.size() ? "Yes" : "No") << endl;
    return 0;
}

