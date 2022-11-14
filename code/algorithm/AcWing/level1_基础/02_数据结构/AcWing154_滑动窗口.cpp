#include <iostream>

using namespace std;

const int N = 100010;

int n, k;
int a[N], q[N];

int main()
{
    scanf("%d", &n, &k);
    for(int i = 0; i < n; ++ i ) scanf("%d", &a[i]);

    int hh = 0, tt = -1;
    for (int i = 0; i < n; ++ i )
    {
        // 判断队头是否划出窗口, (i-k+1): 算出当前队头下标 
        if (hh <= tt && i - k + 1 > q[hh]) ++ hh;
        // 如果新插入的数比队尾要小就没用了, 弹出队尾
        while (hh <= tt && a[q[tt]] >= a[i]) -- tt;
        q[ ++ tt] = i;
        // 如果是前 k 个数的话
        if (i >= k - 1) printf("%d", a[q[hh]]);
    }
    puts("");
}