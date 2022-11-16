//    前面的数和后面的数大就是一组逆序对
// 1) 将整个区间一分为二
//    [L,R] -> [L,mid], [mid+1,R]
// 2) 归并排序[L,mid]和[mid+1,R]
// 3) 归并, 将左右两个有序区间合并为一个有序区间
// 归并了也没关系, 归并排序相对顺序不变, 所以, 左半边一定和右半边组成逆序对
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int q[N], tmp[N];

LL merge_sort(int q[], int l, int r)
{
    if (l >= r) return 0;
    
    int m = l + r >> 1;
    LL res = merge_sort(q, l, m) + merge_sort(q, m + 1, r);

    int k = 0, i = l, j = m + 1;
    // 如果前面大于后面就是一组逆序对
    while (i <= m && j <= r)
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];
        else
        {
            res += m - i + 1;       // 算出 q[i] 比 q[j] 大的数, 因为有序只要 i 比 j 大后面都比 j 大 
            tmp[k ++ ] = q[j ++ ];
        }
    

    while (i <= m) tmp[k ++ ] = q[i ++ ];
    while (j <= r) tmp[k ++ ] = q[j ++ ];
    for (int i = l, j = 0; i <= r; ++ i, ++ j ) q[i] = tmp[j]; 
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i ) scanf("%d", &q[i]);
    cout << merge_sort(q, 0, n - 1) << endl;
}