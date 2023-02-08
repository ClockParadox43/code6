// windy数:不含前导0且相邻两数之差至少为2的正整数被称为windy数
// 求A~B之间有多少个windy数
// ps:这道题不能有前导0, 上一题是允许有前导0出现的
//    因为上一题, 要求升序, 所以, 最高位为0也是符合条件的
//    因为上一题不能包含前导0, 所以最高位只能从1开始填
//    例子: 147, 对于数字游戏来说补上0 -> 0147, 是符合条件的
//          但是对于 wendy数来说, 0147 相邻两数的差就会 < 2(0和1), 所以我们需要把包含前导0的位数特判断掉 
#include <iostream>
#include <vector>

using namespace std;

const int N = 11;

int l, r;
int f[N][10];

void init()
{   
    // f[i][j]状态表示: 最高位为j, 一共有i位, 差值至少为2的数的方案数
    // ps:要从0开始, 因为状态表示时, 存的是包含前导0的情况, 因为是从低位开始的
    //          例:20, f[2][2]:一共2位数字最高位填2, 他会从 f[1][0] 转移过来
    //             但是f[1,0]的初始化为0, 那么20就会被忽略掉
    for (int i = 0; i <= 9; ++ i) f[1][i] = 1;
    for (int i = 2; i < N; ++ i)        // 从第2位开始枚举
        for (int j = 0; j <= 9; ++ j)    // 枚举最高位的数
            for (int k = 0; k <= 9; ++ k)
                if (abs(j - k) >= 2) f[i][j] += f[i - 1][k];
}

int dp(int n)
{
    if (!n) return 0;
    
    vector<int> nums;
    while (n) nums.push_back(n % 10), n /= 10;

    // last: 使last等于0~9之间的任何一个数的差都>=2即可(last >= -2) 
    int res = 0, last = -2;
    for (int i = nums.size() - 1; i >= 0; -- i) // 从高位开始枚举
    {
        int x = nums[i];        // x是当前最高位置, 枚举小于x的数
        for (int j = i == nums.size() - 1; j < x; j ++ ) // 只有从最高位开始算的时候才需要从1开始
            if (abs(j - last) >= 2)
                res += f[i + 1][j]; // 从i位到0位一共i+1位数且最高位为j情况下的方案数 

        // 合法继续循环, 不合法自直接break
        if (abs(x - last) >= 2) last = x;
        else break;

        if (!i) res ++ ;
    }

    // 特殊处理有前导零的数, 低于n位数的数直接特判
    // 最高位从1开始
    for (int i = 1; i < nums.size(); ++ i)
        for (int j = 1; j <= 9; ++ j)
            res += f[i][j];
    return res;
}   

int main()
{
    init();
    int l, r; cin >> l >> r;
    cout << dp(r) - dp(l - 1) << endl;
    return 0;
}