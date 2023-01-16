#include <iostream>

using namespace std;

// 第一次碰到该题要求的是素数: 只有奇数才会是素数
// 如果会增加为数估计循环层数还需要添加
// d1~d3 最多 6 位 -> d1d2d3d3d2d1 
int generate()
{
    // 奇数位
    // d1 as same as d1
    // d2 as same as d2
    // d3
    for (int d1 = 1; d1 <= 9; d1 += 2)
        for (int d2 = 0; d2 <= 9; ++ d2)
            for (int d3 = 0; d3 <= 9; ++ d3)
                int palindrome = 10000 * d1 + 1000 * d2 + 100 * d3 + d2 * 10 + d1;
    // 偶数位
    // d1 as same as d1
    // d2 as same as d2
    // d3 as same as d3
    for (int d1 = 1; d1 <= 9; d1 += 2) 
        for (int d2 = 0; d2 <= 9; d2++)
            for (int d3 = 0; d3 <= 9; d3++)
                int palindrome = 100000 * d1 + 10000 * d2 + 1000 * d3 + 100 * d3 + 10 * d2 + d1;//(处理回文数...)
}

// 判断回文数
// 既然回文数正反一样, 那么我们就把它倒过来
bool is_palindrome(int x)
{
    int tmp = x, ans = 0;
    while (tmp)
    {
        ans = ans * 10 + tmp % 10;
        tmp /= 10;
    }
    if (ans == x) return true;
    else return false;
}

int main()
{
    return 0;
}