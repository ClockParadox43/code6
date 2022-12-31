#include <iostream>

using namespace std;

int main()
{
    int n, m, x; scanf("%d%d%d", &x, &m, &x);
    for (int i = 0; i < n; ++ i ) scanf("%d", &q[i]);
    while (q -- )
    {
        bool flag = false;
        int l, r; scanf("%d%d", &l, &r);
        for (int i = l; i <= r; ++ i )
        {
            for (int j = i + 1; j <= r; ++ j )
                if (q[i] ^ q[j] == x) 
                {
                    flag = true;
                    puts("Yes");
                    break;
                }
            if (flag) break;
        }
        if (!flag) puts("No");
    }
    return 0;
}