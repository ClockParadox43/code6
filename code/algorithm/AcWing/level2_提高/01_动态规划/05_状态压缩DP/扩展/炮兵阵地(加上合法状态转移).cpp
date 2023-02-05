#include <iostream>
#include <vector>

using namespace std;

const int N = 110, M = 1 << 10;
int n, m;
int g[N], cnt[M];
int f[2][M][M];
vector<int> state;
vector<int> head[M];

bool check(int st)
{
    return !(st & st >> 1 || st & st >> 2);
}
int count(int st)
{
    int res = 0;
    while (st) res += st & 1, st >>= 1;
    return res;
}

int main()
{
    cin >> n >> m;
    for (int i = 1, j = 0; i <= n; ++ i, j = 0)
        for (char c; j < m && cin >> c; ++ j)   // 压行
            g[i] += (c == 'H') << j;    
        
    // 找出所有合法状态
    // 统计1的个数也就是摆放了几个炮兵
    for (int st = 0; st < 1 << m; ++ st)
        if (check(st))
            state.push_back(st), cnt[st] = count(st);

    //找出所有合法状态的合法转移
    // 两行之间没有交集, a能转移到b
    for (int cur_st: state)
        for (int pre_st: state)
            if (!(cur_st & pre_st))
                head[cur_st].push_back(pre_st);
    // head的下标是一个状态, 存入的也是一个状态

    // st:当前所有合法状态
    for (int i = 1; i <= n; ++ i)
        for (int st: state)        // 枚举所有状态
            if (!(g[i] & st))      // 不存在空地
                for (int p1: head[st])     // 所有能转移到p1的合法状态
                    for (int p2: head[p1]) // p1能来到p2的状态
                        if (!(st & p2))      // 如果当前状态能来到p2
                            f[i & 1][st][p1] = max(f[i & 1][st][p1], f[i-1 & 1][p1][p2] + cnt[st]);
    
    int res = 0;
    for (int st: state)
        for (int pre: head[st])
            res = max(res, f[n & 1][st][pre]);
    //output
    cout << res << endl;
    return 0;
}