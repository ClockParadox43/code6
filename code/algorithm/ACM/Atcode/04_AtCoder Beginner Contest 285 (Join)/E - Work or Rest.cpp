// 定义一周有n天, 其中可能有 m 天休息日, n-m 天工作日, 周是连续的, 
// 第一周第二周第三周...排下去. 注意这个 m 题目未要求, 但 m 必须大于 1
// 给定一个序列A[N], 下标从一开始
// 现在工作日会有产能, 定义为工作日d产能: Bd=Amin(pre, suf), pre为 d 距离上一次休息日的天数, suf为距离最近后一次休息日的距离
// 如果 Bd=0  为休息日则, 问如何安排休息日, 可以使一周的产能最大, 求出最大产能
//
// 就是定义dp[i][j]:考虑完前i天后, 目前有 j 天连续的工作日的最大产能, 
//      例如:状态dp[5][2]: _ _ 1 0 0,前面的 _ 我们不关心，我们只看最后有多少天连续
//  转移方程:
//      dp[i + 1][j + 1] = dp[i][j]
//      dp[i + 1][0] = dp[i][j] + B[j]        
#include <iostream>

using namespace std;

int main()
{
    return 0;
}