//           3 6 1 4  2  5  7
// 开始时间: 0 3 9 10 14 16 21
//
//           1 2 3 4 5  6  7
// 排序对比: 0 1 3 6 10 15 21
// 
// 每个同学的等待时间都是前几个同学打水时间之和
// 得出公式:3*6 + 6*5 + 1*4 + 4*3 + 2*2+ 5*1    
//              -> 后面 6 名同学都等了 3 分钟, 后面 5 名同学等了 5 分钟...
//
//   总时间 = t1(n-1) + t2(n-2) + t3(n-3) + ... + tn(1) 
//              -> ti 代表第 i 个人打水的时间, (n-1) 代表正在等待的人数
//
//   每个人所等待时间的累加就是总时间 
//
//
//   ti > ti + 1
// 前: ti(n-i) + ti+1(n-i-1)
// 后: ti+1(n-i) + ti(n-i-1)
//
// ti(n-i) + ti+1(n-i-1) - ti+1(n-i) + ti(n-i-1)
// = ti + ( (ti+1)n - (ti+1)i - (ti+1) - (ti+1)n + (ti+1)i)
// = ti - (ti+1)
// 
// ∵ ti > ti + 1 
//    ti - (ti + 1) > 0 
// 因为前面 - 后面 > 0, 这就矛盾了
// 所以排序后总时间就会降低
// 低作业的优先
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010;

int n;
int t[N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &t[i]);

    sort(t, t + n);
    // reverse(t, t + n);

    LL res = 0;
    for (int i = 1; i <= n; ++i) 
        res += t[i] * (n - i);

    printf("%lld", res);

    return 0;
}


