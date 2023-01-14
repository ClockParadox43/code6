// https://www.luogu.com.cn/problem/solution/AT_abc281_e
// 数字模拟窗口, 思想是暴力插入
#include <iostream>
#include <vector>
#define pb push_back
#define fst first
#define scd second 

using namespace std;
typedef long long LL; 
typedef pair<int, int> PII;
const int N = 2e5 + 5;

int n, m, k;    // m:窗口, k:在升序中找前 k 个数, n-m+1: 轮数
LL sum; 
int val[N];
vector<int> a;  // 维持了一个窗口

// lower_bound():
//     用于在指定区域内查找大于目标值的第一个元素
//     使用该函数在制定范围查找某个元素, 最终查找到的不一定是和目标值相等的元素
//     还可能是比目标值大的元素
// 
// 当查找成功时, 该函数还会返回一个正向迭代器, 迭代器指向找到的元素, 
// 反之, 如果查找失败, 迭代器的指向和 last 迭代器相同
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    a.pb(-1);
    for (int i = 1; i <= n; ++ i)
    {
        scanf("%d", &val[i]);

        // 窗口还没有形成
        // 由于不需要删除元素, 所以直接暴力 insert 即可
        if (i <= m)   
        {
            // 找到大于 val[i] 的第一个元素, 将 val[i] 插入在 大于 val[i] 的数的前面
            a.insert(lower_bound(a.begin(), a.end(), val[i]), val[i]);  
            // i = m 时, 统计一下前 k 个数的和 sum (方便滑动) 
            if (i == m) { for (int j = 1; j <= k; ++ j) sum += a[j]; } 
        }
        else
        {
            // 窗口已经形成,
            // 有影响的情况, sum = val[i] - a[k]
            // 插入位置(找到 > 要插入的数(val[i]) 的最小的数的位置)
            // 找到要插入的迭代 - 开始位置的迭代(等价变换成下标)
            // 想以某个下标作为开头(之前也还有下标), 想得到后面下标的位置
            //      - 将后面下标 - 以它开头的下标, 就是后面下标的位置
            int pos = lower_bound(a.begin(), a.end(), val[i]) - a.begin();
            // 如果对答案有影响加上 val[i] 并挤掉当前的 a[k](最后一个数)
            // 会影响答案的仅仅只是前 k 个数, 如果新来的数在排序后的靠后的位置, 那么不影响 sum
            if (pos <= k) sum += val[i] - a[k]; 
            a.insert(a.begin() + pos, val[i]);
            // i-m过期的下标(过期的值, i-m+1 窗口 hh 的位置, -1, 过期的值)
            // 在排序后的数组内找到这个值
            pos = lower_bound(a.begin(), a.end(), val[i - m]) - a.begin(); 
            if (pos <= k) sum += -a[pos] + a[k + 1]; // 如果对答案有影响, 减去 a[pos] 并容下当前的 a[k + 1]
            a.erase(a.begin() + pos);   // 暴力删除
        }
        if (i >= m) printf("%lld ", sum);
    }
    return 0;
}