#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

const int MAXN = 1003;

int n, ans, ansl;
int w[MAXN], f[MAXN], q[MAXN];

int main()
{
    string line;
    getline(cin, line);
    stringstream ssin(line);
    // 把一整行的所有整数都读进来
    while (ssin >> w[n]) n ++ ;

    for (int i = 0; i < n; ++ i)
    {
        f[i] = 1;
        for (int j = 0; j < i; ++ j)
            if (w[i] <= w[j]) f[i] = max(f[i], f[j] + 1);
        ans = max(ans, f[i]);

        int k = 0; 
        while (k < ansl && w[i] > q[k]) ++ k;   // 出现单调上升的情况
        if (k == ansl) q[ansl ++ ] = w[i];      // 来到末尾就开辟新的
        else q[k] = w[i];   // 否则就覆盖
    }
    printf("%d\n%d\n", ans, ansl);
    return 0;
}