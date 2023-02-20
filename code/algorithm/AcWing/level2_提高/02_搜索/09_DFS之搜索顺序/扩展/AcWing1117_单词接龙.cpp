// 思路:字符串替换, 主串从后往前遍历, 子串从前往后用substr截取, 相等就替换, 然后一直搜下去
// 小技巧:
//      因为题目给了开头字母, 但是不能替换整个串, 所以开头字母补一个字符
//      再dfs, 直接搜到最大值, 最后答案减1即可

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

const int N = 25;

int n, ans;
string s[N];
int st[N];

void dfs(string dragon, int last)
{
    st[last] ++ ;
    ans = fmax(ans, dragon.size());
    
    string t;
    for (int i = 0; i < n; ++ i)    // 遍历所有字符串
        for (int j = dragon.size() - 1, k = 1; j > 0 && k < (int)s[i].size(); -- j, ++ k)
            if (st[i] < 2 && dragon.substr(j) == s[i].substr(0, k))
            {
                t = dragon + s[i].substr(k);
                // t = dragon.substr(0, dragon.size() - k) + s[i];
                dfs(t, i);
            }
    st[last] -- ;
            
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> s[i];
    
    string start;
    cin >> start;
    start = " " + start;    // 字母前面添加一个字符, 再dfs所有串
    
    dfs(start, n);
    
    cout << ans - 1 << endl;
    return 0;
}