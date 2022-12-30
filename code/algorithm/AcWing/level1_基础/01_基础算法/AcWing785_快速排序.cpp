#include <iostream>

using namespace std;

const int N = 100010;

int a[N];

void quick_sort(int* q, int l, int r)
{
    if (l >= r) return;
    int i = l - 1, j =  r + 1, x = q[l + r >> 1];   // 因为先往回退一次, 为了保证判断的是有效数字, 先把两个指针往中间移动一次
    while (i < j)
    {
        do i ++ ; while (q[i] < x);     // 如果 i 找到大于 x 的, 就停下来
        do j -- ; while (q[j] > x);     // 如果 i 找到小于 x 的, 就停下来 
        if (i < j) swap(q[i], q[j]);        
    }
    quick_sort(q, l, j);    // 左半区间继续递归
    quick_sort(q, j + 1, r);    
}

int main()
{
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++ i ) scanf("%d", &a[i]);
    quick_sort(a, 0, n);
    for (int i = 1; i <= n; ++ i ) printf("%d ", a[i]);     // 因为初始化数组都是 0, 先往后跳一次一定会卡在值为 0 的格子, 所以会往后交换  
    return 0;
}