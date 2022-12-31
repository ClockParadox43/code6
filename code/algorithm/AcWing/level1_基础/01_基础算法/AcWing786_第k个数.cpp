#include <iostream>

using namespace std;

const int N = 100010;

int n, k, a[N];

// SL 是分界点: 快排思想是将大于 pivot 的数放右边
//             小于 pivot 的数放左边
//             sl(左部分数的长度), k(排序后第几小的数)
//             如果 k 小于 sl(做部分的数一定比 pivot 小), 那就递归左边
//             否则递归右边 
int quickfind(int l, int r, int k) 
{
    // 前半部分和快排完全相同
    if (l >= r) return a[r];
    int i = l - 1, j = r + 1, x = a[l + r >> 1];
    while (i < j) 
    {
        do i++; while (a[i] < x);
        do j--; while (a[j] > x);
        if (i < j) swap(a[i], a[j]);
    }
    // 求出 SL 的长度 (分界点 - 左边界 + 1)
    // SL:排序后左半部分的长度
    int SL = j - l + 1;
    // 情况 A: 要找的数在左半部分
    if (k <= SL) return quickfind(l, j, k);
    // 情况 B: 要找的数在右半部分
    else return quickfind(j + 1, r, k - SL);
}
// 没明白值和排序后下标的关系


int main() 
{
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << quickfind(0, n - 1, k) << endl;
    return 0;
}
