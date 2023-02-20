// 思路:将能拼接的字符预处理出来(建图), 然后暴搜所有可能性

#include <iostream>
#include <string>
#include <cmath>

using namespace std;
const int N = 25;

int n, ans;
string worlds[N];
int g[N][N], used[N];    // 第i号个字符串和第j个字符串的重合部分最小为g[i,j]
                         // 因为我们要使龙最长, 所以重合部分就要最小


// last:代表最后一字符的编号
void dfs(string dragon, int last)
{
    ans = fmax(dragon.size(), ans);
    
    used[last] ++ ;
    for (int i = 0; i < n; ++ i)
        if (g[last][i] && used[i] < 2)
            dfs(dragon + worlds[i].substr(g[last][i]), i);   // 因为不能重合所以worlds[i]从g[last][i]开始截
    used[last] -- ;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> worlds[i];
    

    char start;
    cin >> start;
    
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
        {
            auto a = worlds[i], b = worlds[j];
            for (int k = 1; k < fmin(a.size(), b.size()); ++ k)
                if (a.substr(a.size() - k) == b.substr(0, k))   // a串下标从后面开始截, b串下标从开头开始截
                {
                    g[i][j] = k;
                    break;
                }
        }
    
    for (int i = 0; i < n; ++ i)
        if (worlds[i][0] == start)  // 从和start一样的字符开始接龙 start:a, world:at
            dfs(worlds[i], i);
    cout << ans << endl;
    return 0;
}