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
    
    int cnt = 0;
    while (m -- )
    {
        int z, s; scanf("%d%d", &z, &s);
        if (st[cnt] == z)
            cnt = (cnt - s % n + n) % n; 
        else
            cnt = (cnt + n + s) % n;
    }

    cout << name[cnt];
    return 0;
}