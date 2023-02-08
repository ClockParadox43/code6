// 该数字必须满足各位数字之和mod N为0

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 12, M = 102;

int f[N][10][M];  //f[i][j][k] 表示一共有i位, 且最高位数字是j, 且所有位数字和模p位k的数字个数
int p;

int mod(int u,int v)
{
    return (u % v + v) % v;  //c++的%会得到负数, 需要做一个偏移
}

void init()
{
    memset(f, 0, sizeof f);   //多组测试数据, f数组要清空

    // 一位数, 最高数为i, modp的结果
    for(int i = 0; i <= 9; ++ i) f[1][i][i % p] ++;

    for(int i = 2; i < N; ++ i)         // 枚举位数
        for(int j = 0; j <= 9; ++ j)    // 枚举最高位
            for(int k = 0; k < p; ++ k) // 枚举余数
                for(int x = 0; x <= 9; ++ x) // 决策
                    f[i][j][k] += f[i - 1][x][mod(k - j, p)];
}

int dp(int n)
{
    if(!n) return 1;        // 0模任何数的余数都为0, 本来就可以视作一种方案
    int res = 0, last = 0;  // 表示到当前为止, 前面数位上的数字之和, 当前第i位数字为j, 前面数字之和为last

    vector<int> a;
    while(n) a.push_back(n % 10), n /= 10;
    
    // 后i位(包括j这一位)数字之和sum(前n位已经确定了, 后面的数随便填)与last的关系就是(last+sum)%N == 0, 那么sum%N的结果等价于(-last)%N
    // 所以res += f[i+1][j][(-last%N)]; (后面会提到f数组的处理)
    for(int i = a.size() - 1; i >= 0; -- i)
    {
        int x = a[i];    
        for(int j = 0; j < x; ++ j)  //第i位放0~x-1
            res += f[i + 1][j][mod(-last, p)]; //0~i位，所以一共有i+1位, 最高位为j, 

        last += x;
        if(!i && last % p == 0) res ++;     // 如果最后以个数合法加上答案加1
    }
    return res;
}

int main()
{

    int l,r;
    while(cin >> l >> r >> p)
    {
        init();
        cout << dp(r) - dp(l - 1) << endl;
    }

    return 0;
}
