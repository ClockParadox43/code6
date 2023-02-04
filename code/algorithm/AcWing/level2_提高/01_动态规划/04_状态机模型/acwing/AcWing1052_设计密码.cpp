// t 个状态的自动机
#include <iostream>
#include <cstring>

using namespace std;

const int N = 55, mod = 1e9 + 7;

int n, m;
char str[N];
int ne[N];
// ne[]:以i为终点的后缀和从1开始的前缀相等, 后缀长度最长
//      求模板串长度与后缀的最大长度

int f[N][N];

int main()
{
    cin >> n >> str + 1;
    m = strlen(str + 1);
    // 预处理ne[]
    for (int i = 2, j = 0; i <= m; ++ i)   
    {
        while (j && str[i] != str[j + 1]) j = ne[j];    // j+1位置和当前i位置字符不匹配就往后跳
        if (str[i] == str[j + 1]) j ++ ;                // 相等j加1
        ne[i] = j;      // 记录对于后缀的最长前缀
    }

    // 已经匹配了0位, 且匹配的子串的位置是0时的方案数为1 (初始化)
    f[0][0] = 1;
    
    // 枚举密码位
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < m; ++ j) // 把第i位密码匹配到的子串位置都枚举一遍
                                     // j表示第i位密码匹配到的位置, 因为不能包含子串, 所以不能匹配到m这个位置
            for (int k = 'a'; k <= 'z'; ++ k)   // 把第i+1所有可能的字母都枚举一遍
            {
                // 匹配过程:
                // 寻找当第i+1的位置是k时,
                // 并且密码已经生成了第i位,
                // 匹配的子串的位置是j时,能跳到哪个位置
                int u = j;
                while (u && k != str[u + 1]) u = ne[u];
                if (k == str[u + 1]) u ++ ;
                if (u < m) f[i + 1][u] = (f[i + 1][u] + f[i][j]) % mod;
                // 因为是从f[i][j](i+1的位置为k)跳到f[i+1][u]这个位置, 
                // 所以f[i+1][u] = f[i+1][u]+f[i][j]
                // 注:可能存在重边, 因为j不同但ne[j]是相同的, 并且k是相同的, 所以此时
                //    f[i][j1]和f[i][j2]跳到的位置是一样的(k相同, ne[j1]=ne[j2])
                // f[i+1,u]是当前匹配到的位置, f[i,j]:是能转移的位置
            }

    // 最终的答案数为所有走不到m的方案数之和
    int res = 0;
    for (int i = 0; i < m; ++ i) res = (res + f[n][i]) % mod;
    cout << res << endl;
    return 0;
}