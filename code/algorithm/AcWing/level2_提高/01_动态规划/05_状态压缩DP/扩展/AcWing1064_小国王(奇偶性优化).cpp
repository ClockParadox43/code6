#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 11, M = 1 << N, C = N * N;

int n, m, K;
LL f[N][C][M];
int cnt[M];
vector<int> legal_state;
vector<int> state_trans[M];

bool check(int state)
{
    return !(state & state >> 1);
}
int count(int state)
{
    int res = 0;
    for (int i = 0; i < n; ++ i) res += state >> i & 1;
    return res;
}
int main()
{
    cin >> n >> K;
    //预处理所有合法状态
    for (int st = 0; st < 1 << n; ++ st)
        //检查当前状态是否合法
        if (check(st))
            legal_state.push_back(st),
            cnt[st] = count(st);
    m = legal_state.size();
    //预处理所有合法状态的合法转移
    for (auto cur_st: legal_state)
        for (auto to_st: legal_state)
            if (!(cur_st & to_st) && check(cur_st | to_st))//上下不相邻且纵坐标也不相邻
                state_trans[cur_st].push_back(to_st);
    //动态规划
     f[0][0][0] = 1;
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j <= K; ++ j)
            for (auto &state : legal_state)
            {
                f[i & 1][j][state] = 0; //要先清空
                for (auto &pre_st : state_trans[state])
                    if (j - cnt[state] >= 0)
                        f[i & 1][j][state] += f[(i - 1) & 1][j - cnt[state]][pre_st];
            }


    //统计目标状态的所有方案数
    LL res = 0;
    for (auto state: legal_state) res += f[n & 1][K][state];
    cout << res << endl;
    return 0;
}