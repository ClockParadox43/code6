#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 55;

int n;
int w[N];
vector<int> f[N][N];

bool cmp(vector<int> &a, vector<int> &b)
{
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i -- )
        if (a[i] != b[i])
            return a[i] < b[i];
    return true;
}

vector<int> add(vector<int> a, vector<int> b)
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size() || i < b.size(); i ++ )
    {
        if (i < a.size()) t += a[i];
        if (i < b.size()) t += b[i];
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) c.push_back(t % 10), t /= 10;
    return c;
}

vector<int> mul(vector<int> a, LL b)
{
    vector<int> c;
    LL t = 0;
    for (int i = 0; i < a.size(); i ++ )
    {
        t += b * a[i];
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) c.push_back(t % 10), t /= 10;
    return c;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);

    //区间DP
    //此处初始状态f[l][l+1] = 0 初始就是空vector，不用额外设置
    for (int len = 3; len <= n; len ++ )
    {
        for (int l = 1, r; (r = l + len - 1) <= n; l ++ )
        {
            //初始化初始状态
            for (int k = l + 1; k < r; ++ k)
            {
                //w_l * w_k * w_r
                auto new_val = mul(mul({w[l]}, w[k]), w[r]); // 在 C++11 语法里可以直接初始化成一个 vector
                //f[l][k] + f[k][r] + cost
                new_val = add(add(new_val, f[l][k]), f[k][r]);
                //f[l][r] = min(f[l][r], f[l][k] + f[k][r] + w_sum)
                if (f[l][r].empty() || cmp(new_val, f[l][r])) f[l][r] = new_val;
            }
        }
    }
    //输出最终答案
    auto res = f[1][n];
    for (int i = res.size() - 1; i >= 0; i -- ) printf("%d", res[i]);
    puts("");

    return 0;
}
