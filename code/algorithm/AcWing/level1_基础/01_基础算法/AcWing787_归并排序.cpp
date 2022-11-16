#include <iostream>

using namespace std;

const int N = 1000010;

int n;
int q[N], tmp[N];

//    双指针排序的前提是, 两个数组有序
// 1) 确定分界点, m = (l + r) / 2
// 2) 递归排序 left~right
// 3) 归并 -> 合二为一
void merge_sort(int* q, int l, int r)
{
    if (l >= r) return ;            // 一个或者没有的话 return 
    int m = l + r >> 1;
    merge_sort(q, l, m), merge_sort(q, m + 1, r);
    // 归并
    // 如果左半部分小于右半分, 就加入 tmp (将当前区间变有序)
    // 左区间开始, 右区间开始
    int k = 0, i = l, j = m + 1;
    // 不能用 ||, 为了使 q[i] 和 q[j] 都可以进行对比
    while (i <= m && j <= r)
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];        
        else tmp[k ++ ] = q[j ++ ];                      
    while (i <= m) tmp[k ++ ] = q[i ++ ];       // 左区间还有剩余
    while (j <= r) tmp[k ++ ] = q[j ++ ];       // 右区间还有剩余
    for (int i = l, j = 0; i <= r; ++ i, ++ j ) q[i] =  tmp[j];     // 拷贝进原数组
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i ) scanf("%d", &q[i]);
    merge_sort(q, 0, n - 1);
    for (int i = 0; i < n; ++ i ) printf("%d ", q[i]);
    return 0;
}