// 炮的射程不会被山挡住, 炮兵不能摆在有山的地方
// 射程从1格变成了2格 (多加一维数组, 因为和上一行状态也有关系, 
// 因为所有方案的第i-1行和第i行是一样的, 所以集合划分的时候会依据i-2行来划分)
// 求子集最大值
// 
// 状态表示f[i,j,k]:所有已经摆完前i行, 且第i-1行状态是j, 第i行状态是k的所有摆放方案的最大值
#include <iostream>
#include <vector>

using namespace std;
const int N = 11, M = 1 << N;

int n, m;
int g[1010];
vector<int> st;
int f[2][M][M];
int cnt[M];

bool check(int state)
{
    for (int i = 0; i < m; ++ i)
        if ((state >> i & 1) && ((state >> i + 1 & 1) | (state >> i + 2 & 1))) // 第i行是1并且下两行都有1的话, 就不是合法状态
            return false;
    return true;
}

int count(int state)
{
    int res = 0;
    for (int i = 0; i < m; ++ i) res += state >> i & 1;
    return res;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j < m; ++ j)    
        {
            char c; cin >> c;
            g[i] += (c == 'H') << j;
        }
    
    // 预处理合法状态
    // 相邻两个1之间至少隔两块空地
    for (int i = 0; i < 1 << m; ++ i)
        if (check(i)) 
        {
            st.push_back(i);
            cnt[i] = count(i);      // 预处理每个状态中1的个数
        }
        
    // 枚举所有能转移到的状态
    // 能转移搭到的状态之间不能存在交集
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j < st.size(); ++ j)    
            for (int k = 0; k < st.size(); ++ k) 
                for (int u = 0; u < st.size(); ++ u)    // 表示倒数第2行的状态   
                {
                    // a:第i-1行的状态, b:第i行状态, c:第i-2行状态
                    // 枚举第i-2行状态收否能去第i行的状态(和第i-1行一个集合)
                    // 摆放位置是否存在山地
                    int a = st[j], b = st[k], c = st[u];   
                    if (a & b | a & c | b & c) continue;
                    if (g[i - 1] & a | g[i] & b) continue; 
                    f[i & 1][j][k] = max(f[i & 1][j][k], f[i - 1 & 1][u][j] + cnt[b]);      
                    // 第i行(和第i-1行一个集合)和第i-2行((和第i-1行一个集合)), 求max
                    // 都有一个交集是i-1, 所以我们只要累加上第i行的状态数量即可
                }

    // f[4][0][0]:代表前2行一个不放, 第4行一个不放, 第4-1行一个不放, 因为状态是0
    // 该节课的debug可以反复看
    int res = 0;
    for (int i = 0; i < st.size(); i ++ )
        for (int j = 0; j < st.size(); j ++ )
            res = max(res, f[n & 1][i][j]);

    cout << res << endl;
    
    return 0;
}