// 这道题看着虽然不像DP但是可以用集合的角度来思考
// f[i,j]状态表示:
//       集合:以i为右端点, 长度不超过m连续子区间
//            可以按照子序列的终点进行分类
//       状态计算:fi = max(si - sj) (1 <= i - j <= m)
//       
// si作为一个常量可以提到外面去 fi = si - min{sj} (1 <= i - j <= m)
#include <iostream>

using namespace std;

typedef long long ll;
const int N = 3e5 + 10;

int n, m;       // m:最大长度
ll s[N], q[N];

int main()
{
    cin >> n >> m; 
    for (int i = 1; i <= n; ++ i) 
    {
        cin >> s[i]; 
        s[i] += s[i - 1];
    }
    
    ll res = -1e18;
    int hh = 0, tt = 0; q[0] = 0;
    for (int i = 1; i <= n; ++ i)
    {
        while (hh <= tt && i - q[hh] > m) ++ hh;
        res = max(res, s[i] - s[q[hh]]);        
        while (hh <= tt && s[q[tt]] >= s[i]) -- tt; // 使s[i]尽量小, res得到的才更大
        q[ ++ tt] = i;
    }                   
    cout << res << endl;
    return 0;
}