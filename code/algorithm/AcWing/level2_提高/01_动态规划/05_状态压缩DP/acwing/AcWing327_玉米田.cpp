#include <iostream>
#include <vector>

using namespace std;

const int N = 14, M = 1 << N;

int n, m;
vector<int> head[M];
vector<int> st;
int w[N], f[N][M];      // 用二进制记录二维数组

// w[i]是表示第i行田地的二进制串, 如果和当前位置&的结果不为0证明state是不合法的方案

bool check(int state)
{
    for (int i = 0; i < m; ++i)
        if ((state >> i & 1) && (state >> i + 1 & 1))
            return false;
    return true;
}

const int mod = 1e8;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j < m; ++ j)
        {
            int t; cin >> t;
            w[i] += !t << j;
        }
    
    for (int i = 0; i < 1 << m; ++ i)
        if (check(i))
            st.push_back(i);
            
    for (int i = 0; i < st.size(); ++ i)
        for (int j = 0; j < st.size(); ++ j)
        {
            int a = st[i], b = st[j];
            if (!(a & b)) head[i].push_back(j);
        }
    
    f[0][0] = 1;
    for (int i = 1; i <= n + 1; ++ i)   
        for (int a = 0; a < st.size(); ++ a)
            for (int b : head[a])
            {
                if (w[i] & st[a]) continue;
                f[i][a] = (f[i][a] + f[i - 1][b]) % mod;
            }
    cout << f[n + 1][0];
            
}
