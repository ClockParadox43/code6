#include <iostream>
#include <vector>

using namespace std;

const int N = 14, M = 1 << N, mod = 1e8;

int n, m, k;
int g[N];
int f[2][M];
vector<int> state;
vector<int> head[M];

bool check(int state)
{
    return  !(state & state << 1);
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j < m; ++ j)
            cin >> k, g[i] |= !k << j;
    for (int st = 0; st < 1 << m; ++ st)
        if (check(st))
            state.push_back(st);    //预处理合法状态
    for (auto st: state)
        for (auto ne_st: state)
            if (!(st & ne_st))
                head[st].push_back(ne_st);  //预处理合法状态的合法转移
    f[0][0] = 1;
    for (int i = 1; i <= n + 1; ++ i)
        for (auto st: state)
        {
            f[i & 1][st] = 0;
            if (!(st & g[i]))
                for (auto pre_st: head[st])
                    f[i & 1][st] = (f[i & 1][st] + f[(i - 1) & 1][pre_st]) % mod;
        }
    cout << f[(n + 1) & 1][0] << endl;

    return 0;
}