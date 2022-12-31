// 标签:乘法原理
// 该题性质: 只要左边和自己右边不一样, 自己就是孤独的 (最左边和最右边特例) (至少要 3 个才可以 (题目))
// 由于照片长度可以 "无限大" 所以要考虑左右的数量可以构造出的答案数量
#include <iostream>

using namespace std;

typedef long long LL;   // 组合数的乘积可能会很大

const int N = 500010;

int n, cnt;
LL res;
char a[N];
int b[N];   // 记录不同的牛之间是 的 连续情况

int main()
{
    cin >> n >> a+1;
    
    // 记录每个位置的连续情况, 将序列分成一块一块的(意会)
    b[ ++ cnt] = 1;
    for (int i = 2; i <= n; ++ i )
        if (a[i] == a[i - 1]) b[cnt] ++ ;
        else b[ ++ cnt] = 1;

    for (int i = 1; i <= cnt; ++ i )
    {
        if (b[i] == 1) res += (LL)b[i - 1] * b[i + 1];  // 每一个独立的数左右的组合情况
        if (b[i - 1] >= 2) res += b[i - 1] - 1;  // 每个数左边数的组合, 将当前数看做 1(孤独的牛), 和左边连续的牛组合(>=2) 
        if (b[i + 1] >= 2) res += b[i + 1] - 1;  // 每个数右边数的组合
    }
    cout << res << endl;
    return 0;
}