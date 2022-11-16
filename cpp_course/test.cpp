#include <iostream>

using namespace std;

typedef long long LL; 

const int N = 100010;

LL q[N], tmp[N];

LL merge_sort(int* q, int l, int r)
{
    if (l >= r) return 0;
    m = l + r >> 1;
    int res = merge_sort(q, l, m) + merge_sort(q, m + 1, r);
    int k = 0, i = l, j = m + 1;
    while (i <= m && i <= r)
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ]; 
        else
        {
            res = m - i + 1;
            tmp[k ++ ] = q[j ++ ];
        }
    while (i < m) tmp[k ++ ] = q[i ++ ];
    while (j < r) tmp[k ++ ] = q[j ++ ];
    for (int i = l, j = 0; i <= r; ++ i, ++ j ) q[i] = tmp[j];
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i ) scanf("%d", &a[i]);
    cout << merge_sort(q, 0, n-1);
    return 0;
}