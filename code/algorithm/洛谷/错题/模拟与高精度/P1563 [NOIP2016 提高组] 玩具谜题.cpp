#include <iostream>

using namespace std;

const int N = 100010;
string name[N];
int st[N];

// 正向周期 + 反向周期
int main()
{
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i )
        cin >> st[i] >> name[i];
    
    // s:代表状态, t:代表个数
    // cnt: 下标
    int cnt = 0;
    while (m -- )
    {
        int z, s; scanf("%d%d", &z, &s);
        if (st[cnt] == z)                   // 相等就是往右(逆时针, 逆时针就要减去)
            cnt = (cnt - s % n + n) % n; 
        else                                // 不相等就是往左(也就是顺时针)
            cnt = (cnt + n + s) % n;
    }

    cout << name[cnt];
    return 0;
}