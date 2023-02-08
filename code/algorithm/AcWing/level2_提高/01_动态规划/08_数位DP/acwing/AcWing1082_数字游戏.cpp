// 如果当前最高位为n, 并且固定住n, n > n-1的任何数, 那么0~n-1的数字就可以任意选择
// 所以左边的分支可以通过组合数直接求出, 右边分支固定的是次高位, 所以还需要一一枚举
// 其实求的就是当我们最高位固定某个数且总位数固定的时候
// 总共的"不降数"的个数就是我们所求

// 预处理出所有不降数

#include <iostream>
#include <vector>

using namespace std;

const int N = 15;

int f[N][N];

void init()
{
    // 如果只有1位数字的话, 最高位的数字只有它自己, 所以方案数为1
    for (int i = 0; i <= 9; ++ i) f[1][i] = 1;
    
    // 状态表示f[i,j]:最高位为j的时候, 一共有i位不降数的集合
    // 枚举位数 
    for (int i = 2; i < N; ++ i)            // 枚举位数
        for (int j = 0; j <= 9; ++ j)       // 枚举最高位(只从代码上看, 是从低位开始枚举的..)
            for (int k = j; k <= 9; ++ k)   // 因为最高位为j, k从j开始枚举
                f[i][j] += f[i - 1][k];     // 所以f[i,j]的方案数就是以j为最高位,前i-1位的k的方案数的总和
}               

int dp(int n)
{
    if (!n) return 1;
    vector<int> nums;
    while (n) nums.push_back(n % 10), n /= 10;
    // res:[X,Y]中"不降序的方案数"
    // last:前缀的信息, 我们只要保证每一位数比前一位大
    //      所以只要为last赋值, 使得last后面不管接哪个数都成一个单调上升的关系即可
    int res = 0, last = 0;  

    // 该题在处理后面的分支的时候, 实际上只和上一个数有关系
    for (int i = nums.size() - 1; i >= 0; -- i)
    {
        int x = nums[i];
        for (int j = last; j < x; ++ j)
            res += f[i + 1][j]; // i表示的是位数, 包含i,一共还剩下i+1位, 并且最高位填的是j的情况的方案数(左分支)
        if (x < last) break;    // 如果当前这一位是小于last的, 右边的分支就不存在了
        last = x;               // 当前位赋值给last, 枚举下一位
        if (!i) ++ res;         // 右侧分支, 说明每个数都是大于前一个数的, 累加上它自己
    }
    return res;
}

int main()
{
    init();
    int l, r;
    while (cin >> l >> r) cout << dp(r) - dp(l - 1) << endl;
    return 0;
}